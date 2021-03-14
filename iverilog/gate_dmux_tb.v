module test;

    reg in, sel;
    wire a, b;

    initial begin
        #10 in = 0; sel = 0;
        #10 in = 0; sel = 1;
        #10 in = 1; sel = 0;
        #10 in = 1; sel = 1;
     end

    gate_dmux g (in, sel, a, b);
    //gate_mux_gates g (a, b, sel, out);

    initial
        $monitor("At time %t, in = %d, sel = %d, a = %d, b = %d",
                 $time, in, sel, a, b);

endmodule

