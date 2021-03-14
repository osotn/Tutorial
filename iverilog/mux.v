module gate_mux(input a, input b, input sel, output reg out);

    wire not_a, not_b;
    wire a_and_not_b, b_and_not_a;  

    always @ (a or b or sel) begin
        if (sel == 0)
            out <= a;
        else
            out <= b;
    end

endmodule

