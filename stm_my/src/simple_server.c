/*********************************************
 * vim:sw=8:ts=8:si:et
 * To use the above modeline in vim you must have "set modeline" in your .vimrc
 * Author: Guido Socher
 * Copyright: GPL V2
 * See http://www.gnu.org/licenses/gpl.html
 *
 * Ethernet remote device and sensor
 * UDP and HTTP interface 
        url looks like this http://baseurl/password/command
        or http://baseurl/password/
 *
 * Title: Microchip ENC28J60 Ethernet Interface Driver
 * Chip type           : ATMEGA88 with ENC28J60
 * Note: there is a version number in the text. Search for tuxgraphics
 *********************************************/


/*********************************************
 * modified: 2007-08-08
 * Author  : awake
 * Copyright: GPL V2
 * http://www.icdev.com.cn/?2213/
 * Host chip: ADUC7026
**********************************************/
//#include <includes.h>
#include <string.h>
#include "enc28j60.h"
#include "ip_arp_udp_tcp.h"
#include "net.h"

#pragma pack(4)
#include "test.h"
#pragma pack(pop)
/*
#pragma pack(4)
#include "mcast.pb.h"
#include "pb.h"
#include "pb_decode.h"
#include "pb_encode.h"
#pragma pack(pop)
*/


eAdrGD	*pADRGD;
uint8_t* EthSost;
uint8_t* EthBlock;
uint16_t* PORTNUMBER;
uint8_t* IPAddr;
uint8_t* IPAddrMultyCast;
uint8_t* MACAddr;


unsigned int plen;
unsigned int dat_p;
unsigned char ffi=0;
unsigned char fcmd_pos=0;
unsigned char fcmd;

unsigned char cmd_pos=0;
unsigned char cmd;
char str[30];

unsigned char payloadlen=0;
char fstr[30];
char cmdval;

int16_t GlobData;


//extern void delay_ms(unsigned char ms);

// please modify the following two lines. mac and ip have to be unique
// in your local area network. You can not have the same numbers in
// two devices:

// base url (you can put a DNS name instead of an IP addr. if you have
// a DNS server (baseurl must end in "/"):
static char baseurl[]="http://192.168.1.25/";
//static unsigned int myport =PORTNUM; // listen port for tcp/www (max range 1-254)
// or on a different port:
//static char baseurl[]="http://10.0.0.24:88/";
//static unsigned int mywwwport =88; // listen port for tcp/www (max range 1-254)
//
static unsigned int myudpport =1200; // listen port for udp
// how did I get the mac addr? Translate the first 3 numbers into ascii is: TUX


static unsigned char fbuf[BUFFER_SIZE+1];






void BufCpy(char *pp1, char *pp2, int n) { //dest,source,number
        while(n--) *pp1++ = *pp2++;
//        ClrDog;
		}



// takes a string of the form password/commandNumber and analyse it
// return values: -1 invalid password, otherwise command number
//                -2 no command given but password valid
unsigned char analyse_get_url(char *str)
	{
	unsigned char i=0;
	//if (verify_password(str)==0)
		{
		return(-1);
		}
	// find first "/"
	// passw not longer than 9 char:
	while(*str && i<10 && *str >',' && *str<'{')
		{
        if (*str=='/')
			{
            str++;
            break;
        	}
        i++;
        str++;
		}
	if (*str < 0x3a && *str > 0x2f)
		{
        // is a ASCII number, return it
        return(*str-0x30);
		}
	return(-2);
	}

char CheckSum(char *byte, int size)
{
 int i;
 char res = 0;
 for (i=0; i < size; i++)    // 263
 {
	  res = res + byte[i];
 }
 return res;
}

int SocketUpdate(char nSock,char* f_buf,int data_p,int* fbsize)
{
switch (Sockets[nSock].IP_PHASE)
{
	case(ETH_INIT):
			*fbsize=0;return 0;
	case(ETH_HEAD):
		if (!data_p)
		{
			*fbsize=0;
			return 0;
		}
//		else

		//volatile char crc = 55 - CheckSum(&fbuf[data_p], cSizeHead);
	        //if ( crc != fbuf[info_data_len+48) //53] )
	        //	crcflag = 0;

		*EthSost=WORK_UNIT;
		BufCpy((char*)&Sockets[nSock].Header,&f_buf[data_p],cSizeHead);
		Sockets[nSock].NumBlock=Sockets[nSock].Header.NumDirect&0x0F;

		if (Sockets[nSock].NumBlock == 0)
			numB = fbuf[55];

		//if (Sockets[nSock].NumBlock > 0)
		//{
		//	crcH = fbuf[59];
		//	crcH = crcH << 8;
		//	crcH = crcH + fbuf[60];
		//}

/*		Sockets[nSock].IP_PHASE=ETH_HEADRECEIVED;
		*fbsize=0;
		return 0;
	case(ETH_HEADRECEIVED):*/
		fill_tcp_buf(f_buf,1,&Sockets[nSock].Header.NumDirect);
		*fbsize=1;
		if ((Sockets[nSock].Header.NumDirect&0xF0)==OUT_UNIT)
			Sockets[nSock].IP_PHASE=ETH_SENDBLOCK;
		else
			Sockets[nSock].IP_PHASE=ETH_RECVBLOCK;
		return 1;
	case(ETH_SENDBLOCK):
		if (Sockets[nSock].Header.Size>MAX_PACKET_LENGTH)
		{

			fill_tcp_buf(f_buf,MAX_PACKET_LENGTH,((char*)pADRGD[Sockets[nSock].NumBlock].Adr)+Sockets[nSock].Header.Adr);
			Sockets[nSock].Header.Adr+=MAX_PACKET_LENGTH;
			Sockets[nSock].Header.Size-=MAX_PACKET_LENGTH;
			*fbsize=MAX_PACKET_LENGTH;
//			Sockets[nSock].IP_PHASE=ETH_INIT;
			return 1;
		}
		fill_tcp_buf(f_buf,Sockets[nSock].Header.Size,((char*)pADRGD[Sockets[nSock].NumBlock].Adr)+Sockets[nSock].Header.Adr);
		*fbsize=Sockets[nSock].Header.Size;

		Sockets[nSock].IP_PHASE=ETH_INIT;
		*EthSost=OUT_UNIT;

		return 1;
	case(ETH_RECVBLOCK):
		if (Sockets[nSock].Header.Size<=(plen-54))/*info_data_len/*(plen-54)*/
		{
			if ( (Sockets[nSock].NumBlock == 0) && (info_data_len == 93) )
			{
				//crc = 55-CheckSum(&f_buf[data_p], info_data_len-1);
				crc = f_buf[data_p + info_data_len-1];
				size = info_data_len-1;
			}
			else if ( (Sockets[nSock].NumBlock == 0) && (info_data_len == 65) )
			{
				//crc = 55-CheckSum(&f_buf[data_p], info_data_len-1);
				crc = f_buf[data_p + info_data_len-1];
				size = info_data_len-1;
			}
			else {
				size = 0;
			}
			//{
				//crcP = 55 - CheckSum(&fbuf[data_p], Sockets[nSock].Header.Size);
				//if ( crcH != crcP )
				//{
				//	*EthBlock = 0;
				//	plen = 0;
				//	Sockets[nSock].IP_PHASE=ETH_INIT;
				//	flag = 0;
				//	BL = 0;
				//	return 0;
				//}
			//}

			plen=Sockets[nSock].Header.Size;
			*EthBlock=Sockets[nSock].NumBlock;
			*EthSost=IN_UNIT;
			Sockets[nSock].IP_PHASE=ETH_INIT;
		}
		else plen-=54;

//		if ((Sockets[nSock].Header.Adr<pADRGD[Sockets[nSock].NumBlock].MaxSize-plen))/*&&(Sockets[nSock].Header.Adr>=0)
//				&&(Sockets[nSock].Header.Size<pADRGD[Sockets[nSock].NumBlock].MaxSize))*/
//			if ((Sockets[nSock].NumBlock<12)&&((Sockets[nSock].Header.NumDirect&0xF0)==IN_UNIT))
			{
				//if (flag)
				//{
				//	BL = Sockets[nSock].NumBlock;
					NumBlock = Sockets[nSock].NumBlock;
					BufCpy(((char*)pADRGD[Sockets[nSock].NumBlock].Adr)+Sockets[nSock].Header.Adr,&f_buf[data_p],plen);
					Sockets[nSock].Header.Adr+=plen;
				//}
			}
		Sockets[nSock].Header.Size-=plen;
		*fbsize=0;
		return 1;
}
}

int simple_servercycle(void)
{
	uchar tIPAddr[4];
	uint32_t mcport = GD.Control.PortMCast;
	char i,nS,freeSlot;
	unsigned int	j;
//		OSTimeDlyHMSM(0, 0, 0, 50);
        // get the next new packet:
        plen = enc28j60PacketReceive(BUFFER_SIZE, fbuf);
        //USART_DMASendData(USART1,fbuf,plen);

        /*plen will ne unequal to zero if there is a valid packet (without crc error) */
        if(plen==0)
        	{
            return;
        	}
        // arp is broadcast if unknown but a host may also
        // verify the mac address by sending it to 
        // a unicast address.
        if(eth_type_is_arp_and_my_ip(fbuf,plen))
        	{
			make_arp_answer_from_request(fbuf);
			//USART_DMASendText(USART1,"make_arp_answer_from_request\n");
            return;
        	}

        // check if ip packets are for us:
        if(eth_type_is_ip_and_my_ip(fbuf,plen)==0)
        	{
            return;
        	}
        
        if(fbuf[IP_PROTO_P]==IP_PROTO_ICMP_V && fbuf[ICMP_TYPE_P]==ICMP_TYPE_ECHOREQUEST_V)
        	{
            // a ping packet, let's send pong	
			make_echo_reply_from_request(fbuf, plen);
			//USART_DMASendText(USART1,"make_echo_reply_from_request\n");
			return;
        	}
               // tcp port www start, compare only the lower byte

        // **********************************************************************************
        if (fbuf[IP_PROTO_P]==IP_PROTO_UDP_V&&fbuf[UDP_DST_PORT_H_P]==mcport/256&&fbuf[UDP_DST_PORT_L_P]==mcport%256)
        {
        	payloadlen=fbuf[UDP_LEN_L_P]-UDP_HEADER_LEN;

        	Enc((u8*)&fbuf[UDP_DATA_P+64], payloadlen-64);

/*
        	u8 *dst = (u8*)&fbuf[UDP_DATA_P+400];
        	uint maxsize = 100;
            mcast_meteo_msg msg = mcast_meteo_msg_init_zero;
            pb_ostream_t en_stream = pb_ostream_from_buffer(dst, maxsize);
            msg.temperature = 1233;
            msg.has_temperature = true;
            msg.sun_intensity = 1245;
            msg.has_sun_intensity = true;
            msg.wind_direction = 150;
            msg.has_wind_direction = true;
            msg.wind_speed = 1000;
            msg.has_wind_speed = true;
            msg.rain = 1000;
            msg.has_rain = true;
            msg.rh = 8540;
            msg.has_rh = true;
            status = pb_encode(&en_stream, mcast_meteo_msg_fields, &msg);

            //const u8 *src = (u8*)&fbuf[UDP_DATA_P+64];
            //uint size = payloadlen - 64;
            const u8 *src = (u8*)&fbuf[UDP_DATA_P+400];
            uint size = en_stream.bytes_written;

            //u8 c[] = {0x08, 0xdc, 0x29, 0x10, 0xc2, 0x03};
            //const u8 *src = (u8*)&c[0];


            mcast_meteo_msg msg1 = mcast_meteo_msg_init_zero;
            pb_istream_t de_stream = pb_istream_from_buffer(src, size);
            status = pb_decode(&de_stream, mcast_meteo_msg_fields, &msg1);
            if ( status )
            {
            	SetMeteo(msg1);
            };
            */
          }

        //***********************************************************************************

        if (fbuf[IP_PROTO_P]==IP_PROTO_TCP_V&&fbuf[TCP_DST_PORT_H_P]==(*PORTNUMBER)/256&&fbuf[TCP_DST_PORT_L_P]==(*PORTNUMBER)%256)
			{
			nS=101;
			freeSlot=9;
			for (i=0;i<MAX_SOCKET_COUNT;i++)
			{
				Sockets[i].Timeout--;
				if (Sockets[i].Timeout<0)
				{
					Sockets[i].Timeout=0;
					Sockets[i].IP_PHASE=0;
				}
				if (!Sockets[i].IP_PHASE) freeSlot=i;
				BufCpy(tIPAddr,Sockets[i].IP_source,4);
				if (check_ip_scr(fbuf,tIPAddr))
				{
					nS=i;break;
				}
			}
			if (nS>100) nS=freeSlot;
            //nS=0;

			if (fbuf[TCP_FLAGS_P] & TCP_FLAGS_SYN_V)
				{
                make_tcp_synack_from_syn(fbuf);
                // make_tcp_synack_from_syn does already send the syn,ack
        		Sockets[nS].IP_PHASE=ETH_HEAD;
        		Sockets[nS].Timeout=20;
	            BufCpy(Sockets[nS].IP_source,tIPAddr,4);

                return;
            	}
	        if (fbuf[TCP_FLAGS_P] & TCP_FLAGS_ACK_V)
				{
	            GlobData++;
	            init_len_info(fbuf); // init some data structures
	            // we can possibly have no data, just ack:
	            dat_p=get_tcp_data_pointer();
	            if (dat_p==0)
					{
	                if (fbuf[TCP_FLAGS_P] & TCP_FLAGS_FIN_V)
						{
	                    // finack, answer with ack
	                    make_tcp_ack_from_any(fbuf);
	                    return;
	                	}
	                // just an ack with no data, wait for next packet
	                }
	            else
	            {
					j=checksum(&fbuf[IP_SRC_P], 8+TCP_HEADER_LEN_PLAIN+info_data_len,2);
					if (j)	return;

	            }
	            check_ip_scr(fbuf,tIPAddr);
//	            GlobData++;
	            BufCpy(Sockets[nS].IP_source,tIPAddr,4);
	            SocketUpdate(nS,fbuf,dat_p,&plen);
	            if (plen)
	            	make_tcp_ack_with_data(fbuf,plen,0); // send data
	            else
	            	make_tcp_ack_from_any(fbuf); // send ack for http get
				return;
				}
			}
	// tcp port www end
}

int simple_server(eAdrGD* fADRGD,uint8_t* fSostEth,uint8_t* nBlock, uint8_t* fIPAddr,uint8_t* fMACAddr,uint8_t* fPORTNUMBER)
	{
	SPI1_Init();

//	Del_1ms(100);
	/*initialize enc28j60*/
	pADRGD=fADRGD;
	EthSost=fSostEth;
	EthBlock=nBlock;
	PORTNUMBER=fPORTNUMBER;
	MACAddr=fMACAddr;
	IPAddr=fIPAddr;
	enc28j60Init(MACAddr);
	init_ip_arp_udp_tcp(MACAddr,IPAddr,*PORTNUMBER);
    //Ö¸Ê¾µÆ×´Ì¬:0x476 is PHLCON LEDA(ÂÌ)=links status, LEDB(ºì)=receive/transmit
    enc28j60PhyWrite(PHLCON,0x7a4);
	enc28j60clkout(2); // change clkout from 6.25MHz to 12.5MHz
//	Del_1ms(20);
	Sockets[0].IP_PHASE=0;
	//init the ethernet/ip layer:
//        return (0);
	}

static uint8_t dis_mac[6] = {0xff,0xff,0xff,0xff,0xff,0xff};
//static uint8_t dis_ip[4] = {192,168,1,106};

static uint8_t ipnetmask[4]={255,255,255,0};

static uint8_t ipid=0x2; // IP-identification, it works as well if you do not change it but it is better to fill the field, we count this number up and wrap.
const uint8_t iphdr[] ={0x45,0,0,0x82,0,0,0x40,0,0x20}; // 0x82 is the total len on ip, 0x20 is ttl (time to live), the second 0,0 is IP-identification and may be changed.
const char ntpreqhdr[] ={0xe3,0,4,0xfa,0,1,0,0,0,1};

#define ETH_HEADER_LEN	14
// values of certain bytes:
#define ETHTYPE_ARP_H_V 0x08
#define ETHTYPE_ARP_L_V 0x06
#define ETHTYPE_IP_H_V  0x08
#define ETHTYPE_IP_L_V  0x00

// ******* IP *******
#define IP_HEADER_LEN	20
// ip.src
#define IP_SRC_P 0x1a
#define IP_DST_P 0x1e
#define IP_HEADER_LEN_VER_P 0xe
#define IP_CHECKSUM_P 0x18
#define IP_TTL_P 0x16
#define IP_FLAGS_P 0x14
#define IP_P 0xe
#define IP_TOTLEN_H_P 0x10
#define IP_TOTLEN_L_P 0x11
#define IP_ID_H_P 0x12
#define IP_ID_L_P 0x13

#define IP_PROTO_P 0x17

#define IP_PROTO_ICMP_V 1
#define IP_PROTO_TCP_V 6
// 17=0x11
#define IP_PROTO_UDP_V 17

void fill_buf_p(uint8_t *buf,uint16_t len, const uint8_t *progmem_s)
{
        while (len){
                *buf= pgm_read_byte(progmem_s);
                buf++;
                progmem_s++;
                len--;
        }
}

void client_ntp_request(uint8_t *buf,uint8_t *ntpip,uint8_t srcport,uint8_t *dstmac)
{
        uint8_t i=0;
        uint16_t ck;
        //
        while(i<6){
                buf[ETH_DST_MAC +i]=dstmac[i]; // gw mac in local lan or host mac
                buf[ETH_SRC_MAC +i]=macaddr[i];
                i++;
        }
        buf[ETH_TYPE_H_P] = ETHTYPE_IP_H_V;
        buf[ETH_TYPE_L_P] = ETHTYPE_IP_L_V;
        fill_buf_p(&buf[IP_P],9,iphdr);
        buf[IP_ID_L_P]=ipid; ipid++;
        buf[IP_TOTLEN_L_P]=0x4c;
        buf[IP_PROTO_P]=IP_PROTO_UDP_V;
        i=0;
        while(i<4){
                buf[IP_DST_P+i]=ntpip[i];
                buf[IP_SRC_P+i]=ipaddr[i];
                i++;
        }
        fill_ip_hdr_checksum(buf);
        buf[UDP_DST_PORT_H_P]=0;
        buf[UDP_DST_PORT_L_P]=0x7b; // ntp=123
        buf[UDP_SRC_PORT_H_P]=10;
        buf[UDP_SRC_PORT_L_P]=srcport; // lower 8 bit of src port
        buf[UDP_LEN_H_P]=0;
        buf[UDP_LEN_L_P]=56; // fixed len
        // zero the checksum
        buf[UDP_CHECKSUM_H_P]=0;
        buf[UDP_CHECKSUM_L_P]=0;
        // copy the data:
        i=0;
        // most fields are zero, here we zero everything and fill later
        while(i<48){
                buf[UDP_DATA_P+i]=0;
                i++;
        }
        fill_buf_p(&buf[UDP_DATA_P],10,ntpreqhdr);
        //
        ck=checksum(&buf[IP_SRC_P], 16 + 48,1);
        buf[UDP_CHECKSUM_H_P]=ck>>8;
        buf[UDP_CHECKSUM_L_P]=ck& 0xff;
        enc28j60PacketSend(90,buf);
}

void send_udp_prepare(uint8_t *buf,uint16_t sport, const uint8_t *dip, uint16_t dport,const uint8_t *dstmac)
{
        uint8_t i=0;
        //
        while(i<6){
                buf[ETH_DST_MAC +i]=dstmac[i]; // gw mac in local lan or host mac  //fc-75-16-4e-59-43
                buf[ETH_SRC_MAC +i]=macaddr[i];
                i++;
        }
        buf[ETH_TYPE_H_P] = ETHTYPE_IP_H_V;
        buf[ETH_TYPE_L_P] = ETHTYPE_IP_L_V;
        fill_buf_p(&buf[IP_P],9,iphdr);
        buf[IP_ID_L_P]=ipid; ipid++;
        // total length field in the IP header must be set:
        buf[IP_TOTLEN_H_P]=0;
        // done in transmit: buf[IP_TOTLEN_L_P]=IP_HEADER_LEN+UDP_HEADER_LEN+datalen;
        buf[IP_PROTO_P]=IP_PROTO_UDP_V;
        i=0;
        while(i<4){
                buf[IP_DST_P+i]=dip[i];
                buf[IP_SRC_P+i]=ipaddr[i];
                i++;
        }
        // done in transmit: fill_ip_hdr_checksum(buf);
        buf[UDP_DST_PORT_H_P]=(dport>>8);
        buf[UDP_DST_PORT_L_P]=0xff&dport;
        buf[UDP_SRC_PORT_H_P]=(sport>>8);
        buf[UDP_SRC_PORT_L_P]=sport&0xff;
        buf[UDP_LEN_H_P]=0;
        // done in transmit: buf[UDP_LEN_L_P]=UDP_HEADER_LEN+datalen;
        // zero the checksum
        buf[UDP_CHECKSUM_H_P]=0;
        buf[UDP_CHECKSUM_L_P]=0;
        // copy the data:
        // now starting with the first byte at buf[UDP_DATA_P]
        //
}

void send_udp_transmit(uint8_t *buf,uint16_t datalen)
{
        uint16_t tmp16;
        tmp16=IP_HEADER_LEN+UDP_HEADER_LEN+datalen;
        buf[IP_TOTLEN_L_P]=tmp16& 0xff;
        buf[IP_TOTLEN_H_P]=tmp16>>8;
        fill_ip_hdr_checksum(buf);
        tmp16=UDP_HEADER_LEN+datalen;
        buf[UDP_LEN_L_P]=tmp16& 0xff;
        buf[UDP_LEN_H_P]=tmp16>>8;
        //
        tmp16=checksum(&buf[IP_SRC_P], 16 + datalen,1);
        buf[UDP_CHECKSUM_L_P]=tmp16& 0xff;
        buf[UDP_CHECKSUM_H_P]=tmp16>>8;
        enc28j60PacketSend(UDP_HEADER_LEN+IP_HEADER_LEN+ETH_HEADER_LEN+datalen,buf);
}
/*
int simple_client(eAdrGD* fADRGD,uint8_t* fSostEth,uint8_t* nBlock, uint8_t* fIPAddr,uint8_t* fMACAddr,uint8_t* fPORTNUMBER)
	{
	SPI1_Init();
	pADRGD=fADRGD;
	EthSost=fSostEth;
	EthBlock=nBlock;
	PORTNUMBER=fPORTNUMBER;
	MACAddr=fMACAddr;
	IPAddr=fIPAddr;
	enc28j60Init(MACAddr);
	enc28j60PhyWrite(PHLCON,0x476);
	init_ip_arp_udp_tcp(MACAddr,fIPAddr,*PORTNUMBER);


	//dat_p=packetloop_arp_icmp_tcp(buf,enc28j60PacketReceive(BUFFER_SIZE, buf));


	buf[UDP_DATA_P]='H';
	buf[UDP_DATA_P+1]='E';
	buf[UDP_DATA_P+2]='L';
	buf[UDP_DATA_P+3]='L';
	buf[UDP_DATA_P+4]='O';
	buf[UDP_DATA_P+5]=' ';
	buf[UDP_DATA_P+6]='W';
	buf[UDP_DATA_P+7]='O';
	buf[UDP_DATA_P+8]='R';
	buf[UDP_DATA_P+9]='L';
	buf[UDP_DATA_P+10]='D';

	//Sockets[0].IP_PHASE=0;

    //make_tcp_ack_from_any(fbuf); // send ack for http get
    //make_tcp_ack_with_data(fbuf,plen,0); // send data

	send_udp_prepare(buf,5001,dis_ip,5001,dis_mac);
	send_udp_transmit(buf,11);

	}

uint8_t UDPzoneOut = 0;
uint8_t UDPzoneCount;
uint8_t UDPstartSend;

void UDPSendDataInit(void)
{
    UDPzoneCount = GD.Control.ConfSTepl;
    UDPstartSend = 0;
}

void UDPStartSend(void)
{
	UDPstartSend =1;
}
*/
/*void UDPSend(void)
{
	int countSensorInPack = 0;
	if (UDPstartSend == 0) return;
	int len, nSens;
	enc28j60PhyWrite(PHLCON,0x476);
	len = 0;
	buf[UDP_DATA_P] = UDPzoneOut;
	len++;
    for(nSens=0;nSens<cConfSSens;nSens++)
	{
    	if (GD.Hot.Tepl[UDPzoneOut].InTeplSens[nSens].RCS == 0)
        {
    		UDPout3 = GD.Hot.Tepl[UDPzoneOut].InTeplSens[nSens].Value;
        	buf[UDP_DATA_P+len] = (uint8_t)GD.Hot.Tepl[UDPzoneOut].InTeplSens[nSens].Value;
        	if (UDPzoneOut == 0)
        		UDPout1 = GD.Hot.Tepl[UDPzoneOut].InTeplSens[0].Value;
        	len++;
        	buf[UDP_DATA_P+len] = GD.Hot.Tepl[UDPzoneOut].InTeplSens[nSens].Value>>8;
        	if (UDPzoneOut == 0)
        		UDPout2 = GD.Hot.Tepl[UDPzoneOut].InTeplSens[0].Value>>8;
        	len++;
       	} else

       	{
       		buf[UDP_DATA_P+len] = 0xFF;
       		len++;
       		buf[UDP_DATA_P+len] = 0xFF;
       		len++;
       	}
    	//buf[UDP_DATA_P+len] = ';';
    	//len++;
	}
    UDPzoneOut++;
    if (UDPzoneOut > UDPzoneCount)
    {
    	UDPzoneOut = 0;
    	UDPstartSend = 0;
    }

	send_udp_prepare(buf,5001,dis_ip,5001,dis_mac);
	send_udp_transmit(buf,len);
}
*/
