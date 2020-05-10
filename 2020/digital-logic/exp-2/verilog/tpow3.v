`timescale 1ns/1ns
`include "pow3.v"
module tpow3;

reg [2:0] in;
wire [5:0] out;

pow3 pow (.in(in), .out(out));

integer i;

initial
begin
    for (i = 0; i < 8; i = i + 1)
        #5 in = i; 
end

initial
    $monitor($stime,, in,,, out);

endmodule // 