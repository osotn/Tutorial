module gate_xor(input a, input b, output out);

    wire not_a, not_b;
    wire a_and_not_b, b_and_not_a;  

    gate_not not1 (.a(a), .out(not_a));
    gate_not not2 (.a(b), .out(not_b));
    gate_and and1 (.a(a), .b(not_b), .out(a_and_not_b));
    gate_and and2 (.a(not_a), .b(b), .out(b_and_not_a));
    gate_or  or1  (.a(a_and_not_b), .b(b_and_not_a), .out(out));


endmodule

