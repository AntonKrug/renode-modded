#define OFFSET     0x30000000
#define REG_CTRL0  (OFFSET + 0x0)
#define REG_CTRL1  (OFFSET + 0x4)
#define REG_VALUE  (OFFSET + 0x8)

asm(".long 0x20010000");
asm(".long main");

int main() {
	int i;

	while (1) {
		for(i=0; i<1000000; i++) {
			*(unsigned int *)REG_CTRL1=0x10;
			volatile unsigned int tmp = *(unsigned int *)REG_CTRL0;
		}
		*(unsigned int *)REG_CTRL1=0xde;
	}
}
