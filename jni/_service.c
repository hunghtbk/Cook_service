#include "lib.h"

FILE *fd ;
int sockfd =0;
    struct sockaddr_in serv_addr;
    struct sockaddr_in clie_addr;
    size_t size;
    int out = 0;
    int i;
    char q[5];
int main()
{
    if((sockfd=socket(AF_INET,SOCK_DGRAM,0))<0) {
    error("Khong tao dc socket");
  }
  
  memset(&serv_addr, '0', sizeof(serv_addr));
  memset(&clie_addr, '0', sizeof(clie_addr));
  memset(msg_rec,'0',sizeof(msg_rec));
  
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(PORT);
  
  int reuse = 1;
  if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,(char *)&reuse,sizeof(int)) < 0 ) error("cant reuse port");
  
  if(bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0) {
    error("Khong bind dc socket");
  }
  fd = fopen("ip_table.txt","w");
  fclose(fd);
  fprintf(stdout,"khoi dong socket lang nghe port 5555\n");
  
  size = sizeof(clie_addr);
  while(!out) {     
    if(recvfrom(sockfd,msg_rec,sizeof(msg_rec),0,(struct sockaddr*)&clie_addr,&size)<0) {
      error("Khong nhan dc ban tin");
    }
    
    if (strstr(&msg_rec[0][0],"REQUEST")) {
      fprintf(stdout,"%s\n",clock_microsecond());
      //fprintf(stdout,"gui lai ban tin nhan duoc %s \n ",&msg_rec[0][0]);
      fprintf(stdout,"%s From: \nIP: %s\n\n",&msg_rec[0][0],inet_ntoa(clie_addr.sin_addr));
      clie_addr.sin_port = htons(PORT);
      
      if(check_ip("ip_table.txt",inet_ntoa(clie_addr.sin_addr))==0)
	  write_file1("ip_table.txt",inet_ntoa(clie_addr.sin_addr));
	  
      if(sendto(sockfd,MSG1,sizeof(MSG1),0,(struct sockaddr*)&clie_addr,sizeof(clie_addr)) < 0) {
	error("Khong gui dc");
      }
    }
    else 
    {
      if (strstr(&msg_rec[0][0],"RESPONSE")) {			// nhan lai ban tin RESPONSE xu li luu ip
      //fprintf(stdout,"\nRESPONSE\nFrom \nIP: %s\nPort: %i\n",inet_ntoa(clie_addr.sin_addr),clie_addr.sin_port);  
      fprintf(stdout,"%s\n",clock_microsecond());
      fprintf(stdout,"%s From: \nIP: %s\n\n",&msg_rec[0][0],inet_ntoa(clie_addr.sin_addr));
      
      if(check_ip("ip_table.txt",inet_ntoa(clie_addr.sin_addr))==0)
	 write_file1("ip_table.txt",inet_ntoa(clie_addr.sin_addr));
	
      }
    else 
    {
      if(msg_rec[1][0] ==58)
      fd = fopen("bk.txt","w");
      fclose(fd);
      fprintf(stdout,"nhan ban tin ip vao bk.txt! :%s\n",&msg_rec[1][0]);
      for(i=0;i<32;i++){
      //if (strstr(&msg_rec[i][0],"")) i =32;
      if(check_ip("bk.txt",&msg_rec[i][0])==0)
      write_file("bk.txt",&msg_rec[i][0]);
      //exit(1);
      }
    }
  }
    
    fprintf(stdout,"nhan q de out\n");
    fscanf(stdin,"%s",q);
    if(strstr(q,"q")) {
      fprintf(stdout,"Goob by");
      out =1;
      
    }
  }
  fprintf(stdout,"Waiting done... Byebye !\n");
  write_file("ip_table.txt","anhduc\n");
  printf("test library \n");

}