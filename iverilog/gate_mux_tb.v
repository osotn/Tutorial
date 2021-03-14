module test;

    reg a, b, sel;
    wire out;

    initial begin
        #10 a = 0; b = 0; sel = 0;
        #10 a = 0; b = 1; sel = 0;
        #10 a = 1; b = 0; sel = 0;
        #10 a = 1; b = 1; sel = 0;
        #10 a = 0; b = 0; sel = 1;
        #10 a = 0; b = 1; sel = 1;
        #10 a = 1; b = 0; sel = 1;
        #10 a = 1; b = 1; sel = 1;
     end

    //gate_mux g (a, b, sel, out);
    gate_mux_gates g (a, b, sel, out);

    initial
        $monitor("At time %t, a = %d, b = %d, sel = %d, out = %d",
                 $time, a, b, sel, out);

endmodule

