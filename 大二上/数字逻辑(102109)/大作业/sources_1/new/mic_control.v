module mic_control(
    input wire clk,               
    input wire rst,              
    input wire M_DATA,            
    output wire M_CLK,           
    output wire M_LRSEL,         
    output reg key_valid,        
    output reg [7:0] key_code,   
    output reg key_released      
);

 
    parameter VOLUME_BASE = 8'd15;    // ����������ֵ
    parameter VOLUME_STEP = 8'd12;    // ��������ֵ
    parameter SILENCE_COUNT = 20;      // ��������������ֵ
    
    // ���Ƶ�����Ʋ��� (0.25�� = 25000000��ʱ������ @100MHz)
    parameter OUTPUT_LIMIT = 25000000;
    
    // ����7�������ļ���
    localparam KEY_DO = 8'h1A;  // Z   ��DO��
    localparam KEY_RE = 8'h22;  // X   ��RE��
    localparam KEY_MI = 8'h21;  // C   ��MI��
    localparam KEY_FA = 8'h2A;  // V   ��FA��
    localparam KEY_SO = 8'h32;  // B   ��SO��
    localparam KEY_LA = 8'h31;  // N   ��LA��
    localparam KEY_SI = 8'h3A;  // M   ��SI��
    
    // ��˷�ʱ������ (3MHz)
    reg [4:0] clk_cnt;
    reg mic_clk;
    
    // ���Ƶ�����Ƽ�����
    reg [31:0] output_counter;
    reg output_ready;
    
    // ������������
    reg [4:0] silence_counter;
    reg was_silent;
    
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            clk_cnt <= 5'd0;
            mic_clk <= 1'b0;
        end
        else if (clk_cnt >= 5'd16) begin
            clk_cnt <= 5'd0;
            mic_clk <= ~mic_clk;
        end
        else begin
            clk_cnt <= clk_cnt + 1'b1;
        end
    end
    
    assign M_CLK = mic_clk;
    assign M_LRSEL = 1'b0;

    // PDM���ݴ���
    reg [7:0] pdm_acc;          // PDM�ۼ���
    reg [7:0] sample_cnt;       // ����������
    reg [7:0] volume;           // ��ǰ����ֵ
    reg [7:0] last_volume;      // ��һ�ε�����ֵ
    reg [2:0] current_note;     // ��ǰ����״̬
    reg [2:0] last_note;        // ��һ������״̬
    reg [19:0] debounce_cnt;    // ȥ����������
    reg note_active;            // ��������״̬
    
    // ���Ƶ�������߼�
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            output_counter <= 0;
            output_ready <= 1'b1;
        end
        else begin
            if (output_counter >= OUTPUT_LIMIT) begin
                output_counter <= 0;
                output_ready <= 1'b1;
            end
            else begin
                output_counter <= output_counter + 1;
                if (key_valid)
                    output_ready <= 1'b0;
            end
        end
    end
    
    // PDM��������������
    always @(posedge mic_clk or posedge rst) begin
        if (rst) begin
            pdm_acc <= 8'd0;
            sample_cnt <= 8'd0;
            volume <= 8'd0;
            last_volume <= 8'd0;
        end
        else begin
            if (sample_cnt < 8'd128) begin
                pdm_acc <= pdm_acc + M_DATA;
                sample_cnt <= sample_cnt + 1'b1;
            end
            else begin
                last_volume <= volume;
                volume <= pdm_acc;
                pdm_acc <= 8'd0;
                sample_cnt <= 8'd0;
            end
        end
    end
    
    // ����������������
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            current_note <= 3'd0;
            last_note <= 3'd0;
            key_valid <= 1'b0;
            key_released <= 1'b0;
            key_code <= 8'h00;
            debounce_cnt <= 20'd0;
            note_active <= 1'b0;
            silence_counter <= 0;
            was_silent <= 1'b1;
        end
        else begin
            // Ĭ�ϸ�λ�����ź�
            key_valid <= 1'b0;
            key_released <= 1'b0;
            
            // ��������ȥ����
            if (debounce_cnt < 20'h3FFFF) begin
                debounce_cnt <= debounce_cnt + 1'b1;
            end
            else begin
                debounce_cnt <= 20'd0;
                last_note <= current_note;
                
                // �������
                if (volume < VOLUME_BASE) begin
                    if (silence_counter < SILENCE_COUNT)
                        silence_counter <= silence_counter + 1;
                    else if (!was_silent && note_active) begin
                        key_released <= 1'b1;
                        note_active <= 1'b0;
                        was_silent <= 1'b1;
                    end
                end
                else begin
                    silence_counter <= 0;
                    was_silent <= 1'b0;
                    
                    // ֻ�е�output_readyΪ1ʱ�Ŵ����µ�����
                    if (output_ready) begin
                        // ������������
                        if (volume >= VOLUME_BASE + (VOLUME_STEP * 6))
                            current_note <= 3'd7;  // SI
                        else if (volume >= VOLUME_BASE + (VOLUME_STEP * 5))
                            current_note <= 3'd6;  // LA
                        else if (volume >= VOLUME_BASE + (VOLUME_STEP * 4))
                            current_note <= 3'd5;  // SO
                        else if (volume >= VOLUME_BASE + (VOLUME_STEP * 3))
                            current_note <= 3'd4;  // FA
                        else if (volume >= VOLUME_BASE + (VOLUME_STEP * 2))
                            current_note <= 3'd3;  // MI
                        else if (volume >= VOLUME_BASE + VOLUME_STEP)
                            current_note <= 3'd2;  // RE
                        else
                            current_note <= 3'd1;  // DO
                            
                        // �����仯ʱ���������¼�
                        if (current_note != last_note || !note_active) begin
                            note_active <= 1'b1;
                            key_valid <= 1'b1;
                            case (current_note)
                                3'd1: key_code <= KEY_DO;
                                3'd2: key_code <= KEY_RE;
                                3'd3: key_code <= KEY_MI;
                                3'd4: key_code <= KEY_FA;
                                3'd5: key_code <= KEY_SO;
                                3'd6: key_code <= KEY_LA;
                                3'd7: key_code <= KEY_SI;
                                default: key_code <= 8'h00;
                            endcase
                        end
                    end
                end
            end
        end
    end

endmodule