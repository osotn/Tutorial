module gate_dmux(input in, input sel, output reg a, output reg b);

    always @ (in or sel) begin
        if (sel == 0)
            {a, b} <= {in, 1'b0};
        else
            {a, b} <= {1'b0, in}; 
    end

endmodule

