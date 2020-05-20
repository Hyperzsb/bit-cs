`timescale 1ns/1ns
`include "sale.v"
module tsale;

reg coin = 1'b0;
wire juice;
wire[1:0] state;

sale s (.coin(coin), .juice(juice), .state(state));

integer i;

initial
begin
    for (i = 0; i< 20; i = i + 1)
        #5 coin = !coin;
end

initial
    $monitor($stime, coin, juice, state, i);

endmodule // 