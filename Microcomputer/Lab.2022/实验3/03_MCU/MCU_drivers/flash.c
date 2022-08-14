//包含头文件
#include "flash.h"
#include "string.h"
#if(USE_BIOS_FLASH==0)//1代表函数继承自BIOS，0代表使用自带函数
//=================内部调用函数声明=====================================
//======================================================================
//函数名称：flash_write_DoubleWord
//函数返回：0-成功 1-失败
//参数说明：addr：目标地址，要求为4的倍数且大于Flash首地址
//              （例如：0x08000004，Flash首地址为0x08000000）
//       data：写入的双字
//功能概要：Flash双字写入操作
//======================================================================
uint8_t flash_write_DoubleWord(uint32_t addr,uint32_t data_l,uint32_t data_h);

//======================================================================


//=================外部接口函数=========================================
//======================================================================
//函数名称：flash_init
//函数返回：无
//参数说明：无
//功能概要：初始化flash模块
//======================================================================
void flash_init(void)
{
	//解锁Flash控制寄存器(CR)
	if((FLASH->CR & FLASH_CR_LOCK) != 0U)
    {
		FLASH->KEYR = (uint32_t)FLASH_KEY1;
		FLASH->KEYR = (uint32_t)FLASH_KEY2;
    }

    //等待之前最后一个flash操作完成
	while( (FLASH->SR & FLASH_SR_BSY) != 0U);

	//清数据缓冲区
    FLASH->ACR &= ~FLASH_ACR_DCEN_Msk;
    //清闪存即时编程位
    FLASH->CR &= ~FLASH_CR_PG_Msk;
}
//======================================================================
//函数名称：flash_erase
//函数返回：函数执行执行状态：0=正常；1=异常。
//参数说明：sect：目标扇区号（范围取决于实际芯片，例如 STM32L433:0~127,每扇区2KB;
//功能概要：擦除flash存储器的sect扇区
//======================================================================
uint8_t flash_erase(uint16_t sect)
{
	//等待之前最后一个flash操作完成
	while( (FLASH->SR & FLASH_SR_BSY) != 0U);
	//清闪存即时编程位
    FLASH->CR &= ~FLASH_CR_PG;

    //使能扇区擦除
	FLASH->CR |= FLASH_CR_PER;
	//设置擦除的扇区
	FLASH->CR &= ~FLASH_CR_PNB;
	FLASH->CR |= (uint32_t)(sect << 3u);
	//开始扇区擦除
	FLASH->CR |= FLASH_CR_STRT;
	//等待擦除操作完成
	while( (FLASH->SR & FLASH_SR_BSY) != 0U);
	//禁止扇区擦除
	FLASH->CR &= ~FLASH_CR_PER;

    return 0;  //成功返回
}
//======================================================================
//函数名称：flash_write
//函数返回：函数执行状态：0=正常；1=异常。
//参数说明：sect：扇区号（范围取决于实际芯片，例如 STM32L433:0~127,每扇区2KB）
//        offset:写入扇区内部偏移地址（0~2044，要求为0,4,8,12，......）
//        N：写入字节数目（4~2048,要求为4,8,12,......）
//        buf：源数据缓冲区首地址
//功能概要：将buf开始的N字节写入到flash存储器的sect扇区的 offset处
//=======================================================================
uint8_t flash_write(uint16_t sect,uint16_t offset,uint16_t N,uint8_t *buf)
{
	uint32_t addr;    //双字写入绝对地址
	uint32_t i;    //计数，每8字节加1
	uint16_t temp_l_16,temp_h_16;
//	uint16_t temp_l_32,temp_h_32;    //temp_l双字中低位字，temp_h双字中高位字
	uint32_t temp_l_32,temp_h_32;    //temp_l双字中低位字，temp_h双字中高位字
//	uint_64 temp;    //每次写入的双字

	//等待之前最后一个flash操作完成
	while( (FLASH->SR & FLASH_SR_BSY) != 0U);
	//计算双字写入绝对地址
	addr = (uint32_t)(FLASH_BASE+sect*FLASH_PAGE_SIZE+offset);

	//循环写入双字，每8个数写一次，不足8个自动补齐
	for(i = 0; i < N; i+=8)
	{
		temp_l_16 = (uint16_t)((buf[i])|(buf[i+1]<<8));
		temp_h_16 = (uint16_t)((buf[i+2])|(buf[i+3]<<8));
		temp_l_32 = (uint32_t)((temp_h_16<<16)|temp_l_16);

		temp_l_16 = (uint16_t)((buf[i+4])|(buf[i+5]<<8));
		temp_h_16 = (uint16_t)((buf[i+6])|(buf[i+7]<<8));
		temp_h_32 = (uint32_t)((temp_h_16<<16)|temp_l_16);
		//低位字赋值
		//temp_l_32 = (uint_32)((buf[i])|(buf[i+1]<<8)|(buf[i+2]<<16)|(buf[i+3]<<24));
		//高位字赋值
		//temp_h_32 = (uint_32)((buf[i+4])|(buf[i+5]<<8)|(buf[i+6]<<16)|(buf[i+7]<<24));
		//双字赋值
		//temp = (uint_64)((temp_h_32<<32) | temp_l_32);
		//在绝对地址(addr+i)，实现双字写入
		flash_write_DoubleWord((addr+i),temp_l_32,temp_h_32);
	}

	//等待写入操作完成
	while( (FLASH->SR & FLASH_SR_BSY) != 0U);

    return 0;  //成功执行
}

//==========================================================================
//函数名称：flash_write_physical
//函数返回：函数执行状态：0=正常；非0=异常。
//参数说明： addr：目标地址，要求为4的倍数且大于Flash首地址
//              （例如：0x08000004，Flash首地址为0x08000000）
//       cnt：写入字节数目（8~512）
//       buf：源数据缓冲区首地址
//功能概要：flash写入操作
//==========================================================================
uint8_t flash_write_physical(uint32_t addr,uint16_t cnt,uint8_t buf[])
{
	uint32_t i;    //计数，每8字节加1
	uint32_t temp_l,temp_h;    //temp_l双字中低位字，temp_h双字中高位字
//	uint_64 temp;    //每次写入的双字
	//等待之前最后一个flash操作完成
	while( (FLASH->SR & FLASH_SR_BSY) != 0U);

	//循环写入双字，每8个数写一次，不足8个自动补齐
	for(i = 0; i < cnt; i+=8)
	{
		//低位字赋值
		temp_l = (uint64_t)((buf[i])|(buf[i+1]<<8)|(buf[i+2]<<16)|(buf[i+3]<<24));
		//高位字赋值
		temp_h = (uint64_t)((buf[i+4])|(buf[i+5]<<8)|(buf[i+6]<<16)|(buf[i+7]<<24));
		//双字赋值
//		temp = (uint_64)((temp_h<<32) | temp_l);
		//在绝对地址(addr+i)，实现双字写入
		flash_write_DoubleWord((addr+i),temp_l,temp_h);
	}

	//等待写入操作完成
	while( (FLASH->SR & FLASH_SR_BSY) != 0U);

    return 0;  //成功执行
}

//======================================================================
//函数名称：flash_read_logic
//函数返回：无
//参数说明：dest：读出数据存放处（传地址，目的是带出所读数据，RAM区）
//       sect：扇区号（范围取决于实际芯片，例如 STM32L433:0~127,每扇区2KB）
//       offset:扇区内部偏移地址（0~2024，要求为0,4,8,12，......）
//       N：读字节数目（4~2048,要求为4,8,12,......）//
//功能概要：读取flash存储器的sect扇区的 offset处开始的N字节，到RAM区dest处
//=======================================================================
void flash_read_logic(uint8_t *dest,uint16_t sect,uint16_t offset,uint16_t N)
{
	uint8_t *src;
	src=(uint8_t *)(FLASH_BASE+sect*FLASH_PAGE_SIZE+offset);
	memcpy(dest,src,N);
}

//======================================================================
//函数名称：flash_read_physical
//函数返回：无
//参数说明：dest：读出数据存放处（传地址，目的是带出所读数据，RAM区）
//       addr：目标地址，要求为4的倍数（例如：0x00000004）
//       N：读字节数目（0~1020,要求为4，8,12,......）
//功能概要：读取flash指定地址的内容
//======================================================================
void flash_read_physical(uint8_t *dest,uint32_t addr,uint16_t N)
{
	uint8_t *src;
	src=(uint8_t *)addr;
	memcpy(dest,src,N);
}

//======================================================================
//函数名称：flash_protect
//函数返回：无
//参数说明：M：KL25:待保护区域的扇区号入口值，实际保护M~M+3,其中M=0,4,8,......,124
//         KL36(64):待保护区域的扇区号入口值，实际保护M~M+1,其中M=0,2,4,6,......,62
//功能概要：flash保护操作
//说        明：KL25(128)每调用本函数一次，保护4个扇区（M~M+3）128/32=4
//       KL36(64)每调用本函数一次，保护2个扇区（M~M+1） 63/32=2
//======================================================================
void flash_protect(uint8_t M)
{
	uint32_t STRT,END;    //待保护区域的绝对地址，STRT起始地址，END结束地址

	//计算起始地址
    STRT = (uint32_t)(FLASH_PAGE_SIZE*M/0x8u);
    //计算结束地址
    END = (uint32_t)(FLASH_PAGE_SIZE*(M+1)/0x8u);
    //配置相关寄存器
	FLASH->PCROP1SR |= STRT;
	FLASH->PCROP1ER |= END;
}

//======================================================================
//函数名称：flash_isempty
//函数返回：1=目标区域为空；0=目标区域非空。
//参数说明：所要探测的flash区域初始地址
//功能概要：flash判空操作
//======================================================================
uint8_t flash_isempty(uint8_t *buff,uint16_t N)
{
    uint16_t i,flag;
    i = 0;
    flag = 1;
    for(i = 0; i<N; i++)   //遍历区域内字节
    {
	   if(buff[i]!=0xff)   //非空
	   {
		   flag=0;
		   break;
	    }
    }
    return flag;
}

//----------------------以下为内部函数存放处----------------------------
//======================================================================
//函数名称：flash_write_DoubleWord
//函数返回：0-成功 1-失败
//参数说明：addr：目标地址，要求为4的倍数且大于Flash首地址
//              （例如：0x08000004，Flash首地址为0x08000000）
//       data：写入的双字
//功能概要：Flash双字写入操作（STM32L433每次只能实现双字写入，先写低位字，再写高位字）
//======================================================================
uint8_t flash_write_DoubleWord(uint32_t addr,uint32_t data_l,uint32_t data_h)
{
	//清数据缓冲区
	if((FLASH->ACR & FLASH_ACR_DCEN) != 0U)
	{
		FLASH->ACR &= ~FLASH_ACR_DCEN;
	}

	//使能Flash即时编程
    FLASH->CR |= FLASH_CR_PG;

    //先写入低位字
    *(__IO uint32_t*)addr = data_l;

    //再写入高位字
    *(__IO uint32_t*)(addr+4U) = data_h;

    //禁止Flash即时编程
	FLASH->CR &= ~FLASH_CR_PG;

	return 0;    //返回成功
}
#endif
