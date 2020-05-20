module sale(coin, juice, state);

input coin;
output juice;
output state;

reg juice = 1'b0;
reg[1:0] state = 2'b00;

always @(posedge coin) begin
    if(state != 3)
        state = state + 1;
    else begin
        juice = 1'b1;
        #5 juice = 1'b0;
        state = 0;
    end
end


endmodule // 