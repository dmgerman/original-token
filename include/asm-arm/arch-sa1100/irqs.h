multiline_comment|/*&n; * linux/include/asm-arm/arch-sa1100/irqs.h&n; *&n; * Copyright (C) 1996 Russell King&n; * Copyright (C) 1998 Deborah Wallach (updates for SA1100/Brutus).&n; */
macro_line|#ifdef CONFIG_SA1101
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS                 95
DECL|macro|GPAIN0
mdefine_line|#define GPAIN0          32
DECL|macro|GPAIN1
mdefine_line|#define GPAIN1&t;&t;33
DECL|macro|GPAIN2
mdefine_line|#define GPAIN2&t;&t;34
DECL|macro|GPAIN3
mdefine_line|#define GPAIN3&t;&t;35
DECL|macro|GPAIN4
mdefine_line|#define GPAIN4&t;&t;36
DECL|macro|GPAIN5
mdefine_line|#define GPAIN5&t;&t;37
DECL|macro|GPAIN6
mdefine_line|#define GPAIN6&t;&t;38
DECL|macro|GPAIN7
mdefine_line|#define GPAIN7&t;&t;39
DECL|macro|GPBIN0
mdefine_line|#define GPBIN0&t;&t;40
DECL|macro|GPBIN1
mdefine_line|#define GPBIN1&t;&t;41
DECL|macro|GPBIN2
mdefine_line|#define GPBIN2&t;&t;42
DECL|macro|GPBIN3
mdefine_line|#define GPBIN3&t;&t;43
DECL|macro|GPBIN4
mdefine_line|#define GPBIN4&t;&t;44
DECL|macro|GPBIN5
mdefine_line|#define GPBIN5&t;&t;45
DECL|macro|GPBIN6
mdefine_line|#define GPBIN6&t;&t;46
DECL|macro|RESERVED
mdefine_line|#define RESERVED&t;47
DECL|macro|KPXIN0
mdefine_line|#define KPXIN0&t;&t;48
DECL|macro|KPXIN1
mdefine_line|#define KPXIN1&t;&t;49
DECL|macro|KPXIN2
mdefine_line|#define KPXIN2&t;&t;50
DECL|macro|KPXIN3
mdefine_line|#define KPXIN3&t;&t;51
DECL|macro|KPXIN4
mdefine_line|#define KPXIN4&t;&t;52
DECL|macro|KPXIN5
mdefine_line|#define KPXIN5&t;&t;53
DECL|macro|KPXIN6
mdefine_line|#define KPXIN6&t;&t;54
DECL|macro|KPXIN7
mdefine_line|#define KPXIN7&t;&t;55
DECL|macro|KPYIN0
mdefine_line|#define KPYIN0&t;&t;56
DECL|macro|KPYIN1
mdefine_line|#define KPYIN1&t;&t;57
DECL|macro|KPYIN2
mdefine_line|#define KPYIN2&t;&t;58
DECL|macro|KPYIN3
mdefine_line|#define KPYIN3&t;&t;59
DECL|macro|KPYIN4
mdefine_line|#define KPYIN4&t;&t;60
DECL|macro|KPYIN5
mdefine_line|#define KPYIN5&t;&t;61
DECL|macro|KPYIN6
mdefine_line|#define KPYIN6&t;&t;62
DECL|macro|KPYIN7
mdefine_line|#define KPYIN7&t;&t;63
DECL|macro|KPYIN8
mdefine_line|#define KPYIN8&t;&t;64
DECL|macro|KPYIN9
mdefine_line|#define KPYIN9&t;&t;65
DECL|macro|KPYIN10
mdefine_line|#define KPYIN10&t;&t;66
DECL|macro|KPYIN11
mdefine_line|#define KPYIN11&t;&t;67
DECL|macro|KPYIN12
mdefine_line|#define KPYIN12&t;&t;68
DECL|macro|KPYIN13
mdefine_line|#define KPYIN13&t;&t;69
DECL|macro|KPYIN14
mdefine_line|#define KPYIN14&t;&t;70
DECL|macro|KPYIN15
mdefine_line|#define KPYIN15&t;&t;71
DECL|macro|MSTXINT
mdefine_line|#define MSTXINT&t;&t;72
DECL|macro|MSRXINT
mdefine_line|#define MSRXINT&t;&t;73
DECL|macro|TPTXINT
mdefine_line|#define TPTXINT&t;&t;74
DECL|macro|TPRXINT
mdefine_line|#define TPRXINT&t;&t;75
DECL|macro|INTREQTRC
mdefine_line|#define INTREQTRC&t;76
DECL|macro|INTREQTIM
mdefine_line|#define INTREQTIM&t;77
DECL|macro|INTREQRAV
mdefine_line|#define INTREQRAV&t;78
DECL|macro|INTREQINT
mdefine_line|#define INTREQINT&t;79
DECL|macro|INTREQEMP
mdefine_line|#define INTREQEMP&t;80
DECL|macro|INTREQDAT
mdefine_line|#define INTREQDAT&t;81
DECL|macro|VIDEOINT
mdefine_line|#define VIDEOINT&t;82
DECL|macro|FIFOINT
mdefine_line|#define FIFOINT&t;&t;83
DECL|macro|NIRQHCIM
mdefine_line|#define NIRQHCIM&t;84
DECL|macro|IRQHCIBUFFACC
mdefine_line|#define IRQHCIBUFFACC&t;85
DECL|macro|IRQHCIRMTWKP
mdefine_line|#define IRQHCIRMTWKP&t;86
DECL|macro|NHCIMFCLIR
mdefine_line|#define NHCIMFCLIR&t;87
DECL|macro|USBERROR
mdefine_line|#define USBERROR&t;88
DECL|macro|S0_READY_NIREQ
mdefine_line|#define S0_READY_NIREQ&t;89
DECL|macro|S1_READY_NIREQ
mdefine_line|#define S1_READY_NIREQ&t;90
DECL|macro|S0_CDVALID
mdefine_line|#define S0_CDVALID&t;91
DECL|macro|S1_CDVALID
mdefine_line|#define S1_CDVALID&t;92
DECL|macro|S0_BVD1_STSCHG
mdefine_line|#define S0_BVD1_STSCHG&t;93
DECL|macro|S1_BVD1_STSCHG
mdefine_line|#define S1_BVD1_STSCHG&t;94
DECL|macro|USB_PORT_RESUME
mdefine_line|#define USB_PORT_RESUME&t;95
macro_line|#else
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS                 32
macro_line|#endif
DECL|macro|IRQ_GPIO0
mdefine_line|#define&t;IRQ_GPIO0&t;&t;0
DECL|macro|IRQ_GPIO1
mdefine_line|#define&t;IRQ_GPIO1&t;&t;1
DECL|macro|IRQ_GPIO2
mdefine_line|#define&t;IRQ_GPIO2&t;&t;2
DECL|macro|IRQ_GPIO3
mdefine_line|#define&t;IRQ_GPIO3&t;&t;3
DECL|macro|IRQ_GPIO4
mdefine_line|#define&t;IRQ_GPIO4&t;&t;4
DECL|macro|IRQ_GPIO5
mdefine_line|#define&t;IRQ_GPIO5&t;&t;5
DECL|macro|IRQ_GPIO6
mdefine_line|#define&t;IRQ_GPIO6&t;&t;6
DECL|macro|IRQ_GPIO7
mdefine_line|#define&t;IRQ_GPIO7&t;&t;7
DECL|macro|IRQ_GPIO8
mdefine_line|#define&t;IRQ_GPIO8&t;&t;8
DECL|macro|IRQ_GPIO9
mdefine_line|#define&t;IRQ_GPIO9&t;&t;9
DECL|macro|IRQ_GPIO10
mdefine_line|#define&t;IRQ_GPIO10&t;&t;10
DECL|macro|IRQ_GPIO11_27
mdefine_line|#define&t;IRQ_GPIO11_27&t;&t;11
DECL|macro|IRQ_LCD
mdefine_line|#define&t;IRQ_LCD  &t;&t;12&t;/* LCD controller                  */
DECL|macro|IRQ_Ser0UDC
mdefine_line|#define IRQ_Ser0UDC&t;&t;13&t;/* Ser. port 0 UDC                 */
DECL|macro|IRQ_Ser1SDLC
mdefine_line|#define IRQ_Ser1SDLC&t;&t;14&t;/* Ser. port 1 SDLC                */
DECL|macro|IRQ_Ser1UART
mdefine_line|#define IRQ_Ser1UART&t;&t;15&t;/* Ser. port 1 UART                */
DECL|macro|IRQ_Ser2ICP
mdefine_line|#define IRQ_Ser2ICP&t;&t;16&t;/* Ser. port 2 ICP                 */
DECL|macro|IRQ_Ser3UART
mdefine_line|#define IRQ_Ser3UART&t;&t;17&t;/* Ser. port 3 UART                */
DECL|macro|IRQ_Ser4MCP
mdefine_line|#define IRQ_Ser4MCP&t;&t;18&t;/* Ser. port 4 MCP                 */
DECL|macro|IRQ_Ser4SSP
mdefine_line|#define IRQ_Ser4SSP&t;&t;19&t;/* Ser. port 4 SSP                 */
DECL|macro|IRQ_DMA0
mdefine_line|#define IRQ_DMA0 &t;&t;20&t;/* DMA controller channel 0        */
DECL|macro|IRQ_DMA1
mdefine_line|#define IRQ_DMA1 &t;&t;21&t;/* DMA controller channel 1        */
DECL|macro|IRQ_DMA2
mdefine_line|#define IRQ_DMA2 &t;&t;22&t;/* DMA controller channel 2        */
DECL|macro|IRQ_DMA3
mdefine_line|#define IRQ_DMA3 &t;&t;23&t;/* DMA controller channel 3        */
DECL|macro|IRQ_DMA4
mdefine_line|#define IRQ_DMA4 &t;&t;24&t;/* DMA controller channel 4        */
DECL|macro|IRQ_DMA5
mdefine_line|#define IRQ_DMA5 &t;&t;25&t;/* DMA controller channel 5        */
DECL|macro|IRQ_OST0
mdefine_line|#define IRQ_OST0 &t;&t;26&t;/* OS Timer match 0                */
DECL|macro|IRQ_OST1
mdefine_line|#define IRQ_OST1 &t;&t;27&t;/* OS Timer match 1                */
DECL|macro|IRQ_OST2
mdefine_line|#define IRQ_OST2 &t;&t;28&t;/* OS Timer match 2                */
DECL|macro|IRQ_OST3
mdefine_line|#define IRQ_OST3 &t;&t;29&t;/* OS Timer match 3                */
DECL|macro|IRQ_RTC1Hz
mdefine_line|#define IRQ_RTC1Hz&t;&t;30&t;/* RTC 1 Hz clock                  */
DECL|macro|IRQ_RTCAlrm
mdefine_line|#define IRQ_RTCAlrm&t;&t;31&t;/* RTC Alarm                       */
eof
