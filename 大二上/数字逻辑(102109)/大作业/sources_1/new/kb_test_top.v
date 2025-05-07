module top(
    input CLK100MHZ,               
    input CPU_RESETN,              
    input PS2_CLK,                // PS/2 ʱ��
    input PS2_DATA,               // PS/2 ������������
    input SW0,                    // LED����LD0-15������
    input SW8,                    // ������˷�ģʽ
    input SW14,                   // ��SW15һ������Զ���������
    input SW15,                   
    input M_DATA,                 // ��˷���������
    output M_CLK,                 // ��˷�ʱ��
    output M_LRSEL,                
    output wire [15:0] LED,        // 0��7������ʾ���µļ��룬������ʱû��
    output wire AUD_PWM,          // ��������
    output wire AUD_SD,           
    output wire LED16_B,          // ��ɫ��LED16��blue
    output wire LED16_G,          
    output wire LED16_R,          
    output wire LED17_B,         
    output wire LED17_G,         
    output wire LED17_R,           
    output wire [6:0] SEG,        // �߶��������ʾ����
    output wire [7:0] AN,         
    output wire [3:0] VGA_RED_O,  // VGA�� red
    output wire [3:0] VGA_GREEN_O,// VGA�� green 
    output wire [3:0] VGA_BLUE_O, // VGA�� blue 
    output wire VGA_HS,           //  horizontal sync
    output wire VGA_VS            //  vertical sync
);
    
    wire [7:0] key_code, auto_key_code, mic_key_code;
    wire key_valid, key_released;
    wire auto_key_valid, auto_key_released;
    wire mic_key_valid, mic_key_released;
    wire [2:0] led16_rgb, led17_rgb;
    wire [15:0] LED0_15;
    
    // ����Դѡ���߼�
    wire mic_mode = SW8;
    wire auto_play_enable = SW14 || SW15;
    
    // ����ģʽѡ�����յİ����ź�
    wire [7:0] final_key_code = auto_play_enable ? auto_key_code : mic_mode ? mic_key_code : key_code;                           
    wire final_key_valid = auto_play_enable ? auto_key_valid :  mic_mode ? mic_key_valid : key_valid;                        
    wire final_key_released = auto_play_enable ? auto_key_released : mic_mode ? mic_key_released : key_released;

 
    
 
    // ��������
    kb_input keyboard_unit (.clk(CLK100MHZ),.rst(~CPU_RESETN),.PS2_CLK(PS2_CLK),.PS2_DATA(PS2_DATA),.key_code(key_code),.key_valid(key_valid), .key_released(key_released) );   
    // ��˷���Ƶ�Ԫ
    mic_control mic_unit (.clk(CLK100MHZ),.rst(~CPU_RESETN),.M_DATA(M_DATA),.M_CLK(M_CLK),.M_LRSEL(M_LRSEL),.key_code(mic_key_code),.key_valid(mic_key_valid),.key_released(mic_key_released));   
    // �Զ�����ģʽ�£�ģ���������
    auto_play auto_play_unit ( .clk(CLK100MHZ),.rst(~CPU_RESETN),.sw14(SW14),.sw15(SW15),.key_code(auto_key_code),.key_valid(auto_key_valid),.key_released(auto_key_released)); 
        // ��������
    audio_out audio_unit (.clk(CLK100MHZ),.rst(~CPU_RESETN), .key_code(final_key_code), .key_valid(final_key_valid),  .key_released(final_key_released),.audio_pwm(AUD_PWM),.audio_sd(AUD_SD));   
    // LED������
  led_controller led_unit ( .clk(CLK100MHZ),.rst(~CPU_RESETN),.key_code(final_key_code),.key_valid(final_key_valid), .key_released(final_key_released),.sw0(SW0),.led(LED0_15),.led16_rgb(led16_rgb),.led17_rgb(led17_rgb));
        // �߶��������ʾ
    display_control display_unit (.clk(CLK100MHZ),.rst(~CPU_RESETN),.key_code(final_key_code),.key_valid(final_key_valid),.seg(SEG),.an(AN) ); 
    // VGA��ʾ
    vga_controller vga_unit (.CLK100MHZ(CLK100MHZ),.CPU_RESETN(CPU_RESETN),.key_code(final_key_code),.key_valid(final_key_valid), .key_released(final_key_released),.VGA_RED_O(VGA_RED_O),.VGA_GREEN_O(VGA_GREEN_O),.VGA_BLUE_O(VGA_BLUE_O),.VGA_HS(VGA_HS),.VGA_VS(VGA_VS));

    // RGB LED�������
    assign LED16_R = led16_rgb[2];
    assign LED16_G = led16_rgb[1];
    assign LED16_B = led16_rgb[0];
    assign LED17_R = led17_rgb[2];
    assign LED17_G = led17_rgb[1];
    assign LED17_B = led17_rgb[0];
    assign LED = LED0_15;
endmodule