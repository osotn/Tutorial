module gate_mux_gates(input a, input b, input sel, output out);

    wire not_sel;
    wire a_and_not_sel, b_and_sel;

    gate_not not1 (.a(sel), .out(not_sel));
    gate_and and1 (.a(a), .b(not_sel), .out(a_and_not_sel));
    gate_and and2 (.a(b), .b(sel), .out(b_and_sel));
    gate_or  or1  (.a(a_and_not_sel), .b(b_and_sel), .out(out));

endmodule

