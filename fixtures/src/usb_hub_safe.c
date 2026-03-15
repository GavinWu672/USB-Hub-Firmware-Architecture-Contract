static volatile unsigned char g_usb_interrupt_pending;

static void CFU_Handler(void) {
    return;
}

void USB_ISR(void) {
    g_usb_interrupt_pending = 1;
}
