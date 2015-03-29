var n,m,x,y,min:longint;
    t,i:longint;
    bufin,bufout:array[1..65000]of byte;

begin
  assign(input,'chatnoir.in'); reset(input);
  assign(output,'chatnoir.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);


  readln(t);

  for i := 1 to t do
  begin
    readln(n,m,x,y);

    min := x-1;
    if min > n-x then min := n-x;
    if min > y-1     then min := y-1;
    if min > m-y then min := m-y;

    if min >= 5 then writeln('NU') else writeln('DA');
    //writeln(x,' ',n-x+1,' ',y,' ',m-y+1);

  end;



  close(input);
  close(output);
end.