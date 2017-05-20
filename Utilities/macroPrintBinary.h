/* Macro-based solution to the problem of printing integers in the binary format.
 * So far only the 8 and 16-bit integers are supported. But this can be easily
 * extended for 32 and 64-bit integers as well.
 *
 * Usage: 
 * ```
 * const int x = 42;
 * (void)printf("0b%s\n". TO_BIN_16(x)); /* Outputs: 0b0000000000101010 */
 * ```
 * It's perfectly OK that we're using a 32-bit int, it's just that TO_BIN_16
 * will only output its first 16 bits.
 *
 * An important caveat is that you can't actually embed the macro inside a string.
 * Hence the following is illegal. Though one day I believe I would love to figure 
 * out the solution to this problem.
 *
 * ```
 * const int x = 42;
 * (void)printf("0b" TO_BIN_16(x)); /* Error. */
 * ```
 */
 
#ifndef MACRO_PRINT_IN_BINARY_H
#define MACRO_PRINT_IN_BINARY_H

#define TO_BIN_BT0(x)  (((x) & (1 << 0))  ? '1' : '0')
#define TO_BIN_BT1(x)  (((x) & (1 << 1))  ? '1' : '0')
#define TO_BIN_BT2(x)  (((x) & (1 << 2))  ? '1' : '0')
#define TO_BIN_BT3(x)  (((x) & (1 << 3))  ? '1' : '0')
#define TO_BIN_BT4(x)  (((x) & (1 << 4))  ? '1' : '0')
#define TO_BIN_BT5(x)  (((x) & (1 << 5))  ? '1' : '0')
#define TO_BIN_BT6(x)  (((x) & (1 << 6))  ? '1' : '0')
#define TO_BIN_BT7(x)  (((x) & (1 << 7))  ? '1' : '0')
#define TO_BIN_BT8(x)  (((x) & (1 << 8))  ? '1' : '0')
#define TO_BIN_BT9(x)  (((x) & (1 << 9))  ? '1' : '0')
#define TO_BIN_BT10(x) (((x) & (1 << 10)) ? '1' : '0')
#define TO_BIN_BT11(x) (((x) & (1 << 11)) ? '1' : '0')
#define TO_BIN_BT12(x) (((x) & (1 << 12)) ? '1' : '0')
#define TO_BIN_BT13(x) (((x) & (1 << 13)) ? '1' : '0')
#define TO_BIN_BT14(x) (((x) & (1 << 14)) ? '1' : '0')
#define TO_BIN_BT15(x) (((x) & (1 << 15)) ? '1' : '0')

#define TO_BIN_8(x) \
	((char[]){ TO_BIN_BT7(x), TO_BIN_BT6(x), TO_BIN_BT5(x), \
			   TO_BIN_BT4(x), TO_BIN_BT3(x), TO_BIN_BT2(x), \
			   TO_BIN_BT1(x), TO_BIN_BT0(x), '\0' })

#define TO_BIN_16(x) \
	((char[]){ TO_BIN_BT15(x), TO_BIN_BT14(x), \
			   TO_BIN_BT13(x), TO_BIN_BT12(x), TO_BIN_BT11(x), \
			   TO_BIN_BT10(x), TO_BIN_BT9(x),  TO_BIN_BT8(x),  \
			   TO_BIN_BT7(x),  TO_BIN_BT6(x),  TO_BIN_BT5(x),  \
			   TO_BIN_BT4(x),  TO_BIN_BT3(x),  TO_BIN_BT2(x),  \
			   TO_BIN_BT1(x),  TO_BIN_BT0(x), '\0' })
         
#endif /* MACRO_PRINT_IN_BINARY_H */
