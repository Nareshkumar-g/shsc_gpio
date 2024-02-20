#include <iostream>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/io.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>

#ifdef __linux__
#include <sys/io.h>
#endif

#define C_GPIO_PHY_BASE 0xFD6A0000
#define S_GPIO_PHY_BASE 0xFD6D0000

static unsigned int *C_GPIO_MEM_ADDR = nullptr;
static unsigned int *S_GPIO_MEM_ADDR = nullptr;

#define GPP_OUT1_ADDR (C_GPIO_MEM_ADDR ? (C_GPIO_MEM_ADDR) + 0 * 4 : nullptr)
#define GPP_OUT2_ADDR (C_GPIO_MEM_ADDR ? (C_GPIO_MEM_ADDR) + 1 * 4 : nullptr)
#define GPP_OUT3_ADDR (C_GPIO_MEM_ADDR ? (C_GPIO_MEM_ADDR) + 2 * 4 : nullptr)
#define GPP_OUT4_ADDR (C_GPIO_MEM_ADDR ? (C_GPIO_MEM_ADDR) + 3 * 4 : nullptr)
#define GPP_OUT5_ADDR (C_GPIO_MEM_ADDR ? (C_GPIO_MEM_ADDR) + 4 * 4 : nullptr)
#define GPP_OUT6_ADDR (C_GPIO_MEM_ADDR ? (C_GPIO_MEM_ADDR) + 5 * 4 : nullptr)
#define GPP_OUT7_ADDR (C_GPIO_MEM_ADDR ? (C_GPIO_MEM_ADDR) + 6 * 4 : nullptr)
#define GPP_OUT8_ADDR (C_GPIO_MEM_ADDR ? (C_GPIO_MEM_ADDR) + 7 * 4 : nullptr)
#define GPP_OUT9_ADDR (C_GPIO_MEM_ADDR ? (C_GPIO_MEM_ADDR) + 0x0E * 4 : nullptr)
#define GPP_OUT10_ADDR (C_GPIO_MEM_ADDR ? (C_GPIO_MEM_ADDR) + 0x0F * 4 : nullptr)

#define GPP_IN1_ADDR (S_GPIO_MEM_ADDR ? (S_GPIO_MEM_ADDR) + 0 * 4 : nullptr)
#define GPP_IN2_ADDR (S_GPIO_MEM_ADDR ? (S_GPIO_MEM_ADDR) + 1 * 4 : nullptr)
#define GPP_IN3_ADDR (S_GPIO_MEM_ADDR ? (S_GPIO_MEM_ADDR) + 2 * 4 : nullptr)
#define GPP_IN4_ADDR (S_GPIO_MEM_ADDR ? (S_GPIO_MEM_ADDR) + 3 * 4 : nullptr)
#define GPP_IN5_ADDR (S_GPIO_MEM_ADDR ? (S_GPIO_MEM_ADDR) + 4 * 4 : nullptr)
#define GPP_IN6_ADDR (S_GPIO_MEM_ADDR ? (S_GPIO_MEM_ADDR) + 5 * 4 : nullptr)
#define GPP_IN7_ADDR (S_GPIO_MEM_ADDR ? (S_GPIO_MEM_ADDR) + 6 * 4 : nullptr)
#define GPP_IN8_ADDR (S_GPIO_MEM_ADDR ? (S_GPIO_MEM_ADDR) + 7 * 4 : nullptr)
#define GPP_IN9_ADDR (S_GPIO_MEM_ADDR ? (S_GPIO_MEM_ADDR) + 8 * 4 : nullptr)
#define GPP_IN10_ADDR (S_GPIO_MEM_ADDR ? (S_GPIO_MEM_ADDR) + 9 * 4 : nullptr)
#define GPP_IN11_ADDR (S_GPIO_MEM_ADDR ? (S_GPIO_MEM_ADDR) + 10 * 4 : nullptr)
#define GPP_IN12_ADDR (S_GPIO_MEM_ADDR ? (S_GPIO_MEM_ADDR) + 11 * 4 : nullptr)
#define GPP_IN13_ADDR (S_GPIO_MEM_ADDR ? (S_GPIO_MEM_ADDR) + 12 * 4 : nullptr)

void Init_Gpio(void)
{
    unsigned int val = 0x44000200;
    if (GPP_OUT1_ADDR)
        *(GPP_OUT1_ADDR) = val;
    if (GPP_OUT2_ADDR)
        *(GPP_OUT2_ADDR) = val;
    if (GPP_OUT3_ADDR)
        *(GPP_OUT3_ADDR) = val;
    if (GPP_OUT4_ADDR)
        *(GPP_OUT4_ADDR) = val;
    if (GPP_OUT5_ADDR)
        *(GPP_OUT5_ADDR) = val;
    if (GPP_OUT6_ADDR)
        *(GPP_OUT6_ADDR) = val;
    if (GPP_OUT7_ADDR)
        *(GPP_OUT7_ADDR) = val;
    if (GPP_OUT8_ADDR)
        *(GPP_OUT8_ADDR) = val;
    if (GPP_OUT9_ADDR)
        *(GPP_OUT9_ADDR) = val;
    if (GPP_OUT10_ADDR)
        *(GPP_OUT10_ADDR) = val;
}

void Set_InMode(void)
{
    unsigned int val = 0x44000100;
    if (GPP_IN1_ADDR)
        *(GPP_IN1_ADDR) = val;
    if (GPP_IN2_ADDR)
        *(GPP_IN2_ADDR) = val;
    if (GPP_IN3_ADDR)
        *(GPP_IN3_ADDR) = val;
    if (GPP_IN4_ADDR)                                                             
        *(GPP_IN4_ADDR) = val;
    if (GPP_IN5_ADDR)
        *(GPP_IN5_ADDR) = val;
    if (GPP_IN6_ADDR)
        *(GPP_IN6_ADDR) = val;
    if (GPP_IN7_ADDR)
        *(GPP_IN7_ADDR) = val;
    if (GPP_IN8_ADDR)
        *(GPP_IN8_ADDR) = val;
    if (GPP_IN9_ADDR)
        *(GPP_IN9_ADDR) = val;
    if (GPP_IN10_ADDR)
        *(GPP_IN10_ADDR) = val;
    if (GPP_IN11_ADDR)
        *(GPP_IN11_ADDR) = val;
    if (GPP_IN12_ADDR)
        *(GPP_IN12_ADDR) = val;
    if (GPP_IN13_ADDR)
        *(GPP_IN13_ADDR) = val;
}int main(void)
{
    int fd;
    unsigned int *add1;
    unsigned int *add2;

    // Use ioperm for port I/O permissions
    if (ioperm(C_GPIO_PHY_BASE, 0x1000, 1) != 0)
    {
        std::cout << "Failed to set I/O port permissions." << std::endl;
        return 1;
    }

    if (ioperm(S_GPIO_PHY_BASE, 0x1000, 1) != 0)
    {
        std::cout << "Failed to set I/O port permissions." << std::endl;
        return 1;
    }

    fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd < 0)
    {
        std::cout << "cannot open /dev/mem" << std::endl;
        return 1;
    }

    add1 = (unsigned int *)mmap(NULL, 0x1000 & ~(sysconf(_SC_PAGE_SIZE) - 1), PROT_READ | PROT_WRITE, MAP_SHARED, fd, C_GPIO_PHY_BASE);
    add2 = (unsigned int *)mmap(NULL, 0x1000 & ~(sysconf(_SC_PAGE_SIZE) - 1), PROT_READ | PROT_WRITE, MAP_SHARED, fd, S_GPIO_PHY_BASE);
    if (MAP_FAILED == add1)
    {
        perror("mmap failed:");
        return 1;
    }

    C_GPIO_MEM_ADDR = add1 + 0x1E0; // 0x780/4
    S_GPIO_MEM_ADDR = add2 + 0x1C0; // 0x700/4

    Init_Gpio();
    Test_GPO();
    std::cout << "Soc GPIO output Test End!!" << std::endl;
    Set_InMode();
    while (1)
    {
        readinputsts();
        sleep(2);
    }

    return 0;
}


void set_lvl(int portNum, int level)
{
    unsigned int val;

    switch (portNum)
    {
    case 0:
        val = GPP_OUT1_ADDR ? *(GPP_OUT1_ADDR) : 0;
        val &= ~(0x1);
        if (level)
            val |= 0x1;
        if (GPP_OUT1_ADDR)
            *(GPP_OUT1_ADDR) = val;
        break;

    case 1:
        val = GPP_OUT2_ADDR ? *(GPP_OUT2_ADDR) : 0;
        val &= ~(0x1);
        if (level)
            val |= 0x1;
        if (GPP_OUT2_ADDR)
            *(GPP_OUT2_ADDR) = val;
        break;
    case 2:
        val = GPP_OUT3_ADDR ? *(GPP_OUT3_ADDR) : 0;
        val &= ~(0x1);
        if (level)
            val |= 0x1;
        if (GPP_OUT3_ADDR)
            *(GPP_OUT3_ADDR) = val;
        break;
    case 3:
        val = GPP_OUT4_ADDR ? *(GPP_OUT4_ADDR) : 0;
        val &= ~(0x1);
        if (level)
            val |= 0x1;
        if (GPP_OUT4_ADDR)
            *(GPP_OUT4_ADDR) = val;
        break;
    case 4:
        val = GPP_OUT5_ADDR ? *(GPP_OUT5_ADDR) : 0;
        val &= ~(0x1);
        if (level)
            val |= 0x1;
        if (GPP_OUT5_ADDR)
            *(GPP_OUT5_ADDR) = val;
        break;
    case 5:
        val = GPP_OUT6_ADDR ? *(GPP_OUT6_ADDR) : 0;
        val &= ~(0x1);
        if (level)
            val |= 0x1;
        if (GPP_OUT6_ADDR)
            *(GPP_OUT6_ADDR) = val;
        break;
    case 6:
        val = GPP_OUT7_ADDR ? *(GPP_OUT7_ADDR) : 0;
        val &= ~(0x1);
        if (level)
            val |= 0x1;
        if (GPP_OUT7_ADDR)
            *(GPP_OUT7_ADDR) = val;
        break;
    case 7:
        val = GPP_OUT8_ADDR ? *(GPP_OUT8_ADDR) : 0;
        val &= ~(0x1);
        if (level)
            val |= 0x1;
        if (GPP_OUT8_ADDR)
            *(GPP_OUT8_ADDR) = val;
        break;
    case 8:
        val = GPP_OUT9_ADDR ? *(GPP_OUT9_ADDR) : 0;
        val &= ~(0x1);
        if (level)
            val |= 0x1;
        if (GPP_OUT9_ADDR)
            *(GPP_OUT9_ADDR) = val;
        break;

    case 9:
        val = GPP_OUT10_ADDR ? *(GPP_OUT10_ADDR) : 0;
        val &= ~(0x1);
        if (level)
            val |= 0x1;
        if (GPP_OUT10_ADDR)
            *(GPP_OUT10_ADDR) = val;
        break;

    default:
        break;
    }
}

void Test_GPO(void)
{
    int portNum;
    int gpo_level;
    for (portNum = 0; portNum < 10; portNum++)
    {
        std::cout << "set GP-OUT Pin" << portNum << " OUT level(0 or 1): ";
        std::cin >> gpo_level;
        set_lvl(portNum, gpo_level);
    }
}

void readinputsts(void)
{
    unsigned int val;

    if (GPP_IN1_ADDR)
    {
        val = *(GPP_IN1_ADDR);
        val &= 0x00000002;
        std::cout << (val ? "1 " : "0 ");
    }
    if (GPP_IN2_ADDR)
    {
        val = *(GPP_IN2_ADDR);
        val &= 0x00000002;
        std::cout << (val ? "1 " : "0 ");
    }
    if (GPP_IN3_ADDR)
    {
        val = *(GPP_IN3_ADDR);
        val &= 0x00000002;
        std::cout << (val ? "1 " : "0 ");
    }
    if (GPP_IN4_ADDR)
    {int main(void)
{
    int fd;
    unsigned int *add1;
    unsigned int *add2;

    // Use ioperm for port I/O permissions
    if (ioperm(C_GPIO_PHY_BASE, 0x1000, 1) != 0)
    {
        std::cout << "Failed to set I/O port permissions." << std::endl;
        return 1;
    }

    if (ioperm(S_GPIO_PHY_BASE, 0x1000, 1) != 0)
    {
        std::cout << "Failed to set I/O port permissions." << std::endl;
        return 1;
    }

    fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd < 0)
    {
        std::cout << "cannot open /dev/mem" << std::endl;
        return 1;
    }

    add1 = (unsigned int *)mmap(NULL, 0x1000 & ~(sysconf(_SC_PAGE_SIZE) - 1), PROT_READ | PROT_WRITE, MAP_SHARED, fd, C_GPIO_PHY_BASE);
    add2 = (unsigned int *)mmap(NULL, 0x1000 & ~(sysconf(_SC_PAGE_SIZE) - 1), PROT_READ | PROT_WRITE, MAP_SHARED, fd, S_GPIO_PHY_BASE);
    if (MAP_FAILED == add1)
    {
        perror("mmap failed:");
        return 1;
    }

    C_GPIO_MEM_ADDR = add1 + 0x1E0; // 0x780/4
    S_GPIO_MEM_ADDR = add2 + 0x1C0; // 0x700/4

    Init_Gpio();
    Test_GPO();
    std::cout << "Soc GPIO output Test End!!" << std::endl;
    Set_InMode();
    while (1)
    {
        readinputsts();
        sleep(2);
    }

    return 0;
}

    if (GPP_IN6_ADDR)
    {
        val = *(GPP_IN6_ADDR);
        val &= 0x00000002;
        std::cout << (val ? "1 " : "0 ");
    }
    if (GPP_IN7_ADDR)
    {
        val = *(GPP_IN7_ADDR);
        val &= 0x00000002;
        std::cout << (val ? "1 " : "0 ");
    }
    if (GPP_IN8_ADDR)
    {
        val = *(GPP_IN8_ADDR);
        val &= 0x00000002;
        std::cout << (val ? "1 " : "0 ");
    }
    if (GPP_IN9_ADDR)
    {
        val = *(GPP_IN9_ADDR);
        val &= 0x00000002;
        std::cout << (val ? "1 " : "0 ");
    }
    if (GPP_IN10_ADDR)
    {
        val = *(GPP_IN10_ADDR);
        val &= 0x00000002;
        std::cout << (val ? "1 " : "0 ");
    }
    if (GPP_IN11_ADDR)
    {
        val = *(GPP_IN11_ADDR);
        val &= 0x00000002;
        std::cout << (val ? "1 " : "0 ");
    }
    if (GPP_IN12_ADDR)
    {
        val = *(GPP_IN12_ADDR);
        val &= 0x00000002;
        std::cout << (val ? "1 " : "0 ");
    }
    if (GPP_IN13_ADDR)
    {
        val = *(GPP_IN13_ADDR);
        val &= 0x00000002;
        std::cout << (val ? "1 " : "0 ");
    }

    std::cout << std::endl;
}

int main(void)
{
    int fd;
    unsigned int *add1;
    unsigned int *add2;

#ifdef __linux__
    if (0 != iopl(3))
    {
        std::cout << "gpio must run in root mode." << std::endl;
        return 1;
    }
#endif

    fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd < 0)
    {
        std::cout << "cannot open /dev/mem" << std::endl;
        return 1;
    }

    add1 = (unsigned int *)mmap(NULL, 0x1000 & ~(sysconf(_SC_PAGE_SIZE) - 1), PROT_READ | PROT_WRITE, MAP_SHARED, fd, C_GPIO_PHY_BASE);
    add2 = (unsigned int *)mmap(NULL, 0x1000 & ~(sysconf(_SC_PAGE_SIZE) - 1), PROT_READ | PROT_WRITE, MAP_SHARED, fd, S_GPIO_PHY_BASE);
    if (MAP_FAILED == add1)
    {
        perror("mmap failed:");
        return 1;
    }

    C_GPIO_MEM_ADDR = add1 + 0x1E0; // 0x780/4
    S_GPIO_MEM_ADDR = add2 + 0x1C0; // 0x700/4

    Init_Gpio();
    Test_GPO();
    std::cout << "Soc GPIO output Test End!!" << std::endl;
    Set_InMode();
    while (1)
    {
        readinputsts();
        sleep(2);
    }

    return 0;
}