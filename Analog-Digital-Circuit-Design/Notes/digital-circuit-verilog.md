# 数字电路（第三部分：Verilog设计）

## 语法

- 模块定义：`module 模块名(端口1,端口2,端口3,...);`
- 模块定义结束：`endmodule`
- I/O说明：输入 `input 端口名1,端口名2,...,端口名N;` ，输出 `output 端口名1,端口名2,...,端口名N;`
- register型变量（在always块中被赋值的信号）定义：`reg 数据名1,数据名2,...,数据名n;`。定义8位宽的数据：`reg[7:0] data;`      
- assign语句：`assign 方程式;`，一般适合于对**组合逻
辑**进行赋值。
- 数字：`<位宽>'<进制> <数字>` 位宽为对应二进制数的宽度；十进制的数可以缺省位宽和进制说明（二进制b，十六进制h）；x代表不定值,z代表高阻值。
- `if-else`语句、`case-endcase`语句，要在always块内；如执行的语句为多句时，要用`begin-end`语句括起来。
- 位拼接运算符 `{ }`：将两个或多个信号的某些位拼接起来，如`{信号1的某几位,信号2的某几位,...,信号n的某几位}`

### always块

当括号内的表达式的值改变时，就会执行一遍块内语句。（一般用于**时序逻辑**）

~~~verilog
always @(...)
    begin
        // 过程赋值
        // if语句
        // case语句
    end
~~~

posedge与negedge关键字：事件由时钟边沿触发，分别表示信号的上升沿和下降沿。如：

~~~verilog
always @(posedge clk)  // 表示时钟信号clk的上升沿
always @(negedge clk)  // 表示时钟信号clk的下降沿
~~~

always块内是按照指定的顺序执行的；两个或更多个always块之间、always块与assign语句之间，是同时执行（并行执行）的。

## 设计举例

4位全加器

~~~verilog
module add4(cout, sum, a, b, cin);
    output cout;
    output [3:0] sum;
    input [3:0] a, b;
    input cin;
    assign {cout, sum} = a + b + cin;
endmodule
~~~

3-8译码器

~~~verilog
module decoder_38(out,in,en);
    output [7:0] out;
    input [2:0] in;
    input en;
    reg [7:0] out;
    always @(in or en)
      begin
        if (en) out=8'b11111111;
        else
          case(in)
            3'b000: out=8'b11111110;
            3'b001: out=8'b11111101;
            3'b010: out=8'b11111011;
            3'b011: out=8'b11110111;
            3'b100: out=8'b11101111;
            3'b101: out=8'b11011111;
            3'b110: out=8'b10111111;
            3'b111: out=8'b01111111;
          endcase
      end
endmodule
~~~

4位**同步清0、同步预置**二进制计数器

~~~verilog
module counter4(out, cout, data, load, clr, clk);
    output[3:0] out;
    output cout;
    input[3:0] data;
    input load, clr, clk;
    reg[3:0] out;
    always @(posedge clk)
      begin
        if (!clr)  out=0;  // 清零
        else if (load)  out=data;  // 置数
        else  out=out+1;
      end
    assign cout=&out;  // 进位（各位与运算）
endmodule
~~~

4位**异步清0、同步预置**二进制计数器（注意这里异步清零的方法）

~~~verilog
module counter4(out, cout, data, load, clr, clk);
    output[3:0] out;
    output cout;
    input[3:0] data;
    input load, clr, clk;
    reg[3:0] out;
    always @(posedge clk)
      begin
        if (load)  out=data;  // 置数
        else  out=out+1;
      end
    always @(clr) 
      begin 
        if (!clr)  out=0;  // 清零
      end
    assign cout=&out;  // 进位（各位与运算）
endmodule
~~~

4位**同步清0、同步预置**十进制计数器

~~~verilog
module   counter10(out,cout,data,load,clr,clk);
    output[3:0] out;
    output cout;
    input[3:0] data;
    input load, clr, clk;
    reg[3:0] out;
    always @(posedge clk)
      begin
        if (!clr)  out=0;  // 清零
        else if (load)  out=data;  // 置数
        else if (out==9)  out=0;  // 十进制进位
        else  out=out+1;
      end
    assign  cout = (out==9) ? 1 : 0;  // 进位
endmodule
~~~

4位**异步清0、同步预置**十进制计数器

~~~verilog
module   counter10(out,cout,data,load,clr,clk);
    output[3:0] out;
    output cout;
    input[3:0] data;
    input load, clr, clk;
    reg[3:0] out;
    always @(posedge clk)
      begin
        if (load)  out=data;  // 置数
        else if (out==9)  out=0;  // 十进制进位
        else  out=out+1;
      end
    always @(clr) 
      begin 
        if (!clr)  out=0;  // 清零
      end
    assign  cout = (out==9) ? 1 : 0;  // 进位
endmodule
~~~

8位移位寄存器（同步清0，左移）

~~~verilog
module shifter8(dout, din, clk, clr);
    output [7:0] dout;
    input din, clk, clr;
    reg [7:0] dout;
    always @(posedge clk)
      begin
        if (clr)  dout=0;  // 清零
        else begin
                dout=dout<<1;  // 输出信号左移一位
                dout[0]=din;  // 输入信号补到输出信号的最低位
             end
      end
endmodule
~~~

▲ 4选1数据选择器
~~~verilog
module mux4_1(out, in0, in1, in2, in3, sel);
    output out;
    input in0,in1,in2,in3;
    input[1:0] sel;  // 选择信号
    reg out;
    always @(in0 or in1 or in2 or in3 or sel)
        case(sel)
            2'b00: out=in0;
            2'b01: out=in1;
            2'b10: out=in2;
            2'b11: out=in3;
            default: out=2'bx;
        endcase
endmodule
~~~

▲ 可变模k加法/减法计数器（同步清0，同步预置）
~~~verilog
module updown_count(data, clk, clr, load, up_down, out, cout);
    input[7:0] data;
    input clk, clr, load;
    input up_down;
    output[7:0] out;
    output cout;
    reg[7:0] out;
    reg cout;
    always @(posedge clk)
      begin
        if (!clr) out = 0; // 同步清0，低电平有效
        else if (load) out = data; // 同步预置
        else if (up_down)  begin  // 加法计数
            if (out==k-1)  begin // 进位
                out = 0;
                cout = 1;
              end
            else  begin 
                out = out + 1;
                cout = 0;
              end
          end
        else  begin  // 减法计数
            if (out==0)  begin // 进位
                out = k-1;
                cout = 1;
              end
            else  begin 
                out = out - 1;
                cout = 0;
              end
          end
      end
endmodule
~~~
