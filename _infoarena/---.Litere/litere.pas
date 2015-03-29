var n,i,op,j:longint;
    s:ansistring;
    bufin:array[1..65000]of byte;
    sum:int64;
    fr:array[1..26]of longint;

begin
  assign(input,'litere.in'); reset(input);
  assign(output,'litere.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n);
  readln(s);

  for i := 1 to 26 do fr[i] := 0;  sum := 0;

  for i := 1 to n do
  begin
    op := ord(s[i])- $60;
    inc(fr[op]);

    for j := op+1 to 26 do
    begin
      sum := sum + fr[j];
    end;
  end;


  writeln(sum);



  close(input);
  close(output);
end.