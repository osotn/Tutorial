module test;

    reg a, b;
    wire out;

    initial begin
        #10 a = 0; b = 0;
        #10 a = 0; b = 1;
        #10 a = 1; b = 0;
        #10 a = 1; b = 1;
        #10 a = 0; b = 0;
    end

    gate_xor g (a, b, out);

    initial
        $monitor("At time %t, a = %d, b = %d, out = %d",
                 $time, a, b, out);

endmodule

