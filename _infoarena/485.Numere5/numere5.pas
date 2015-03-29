var n:int64;
    i,j,cont:longint;
    bufin:array[1..65000]of byte;
    suma,sumat,x:int64 ;

begin
  assign(input,'numere5.in'); reset(input);
  assign(output,'numere5.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n); suma := 0;  cont := 0;

  for i := 1 to n do
  begin
    for j := 1 to n do
    begin
      read(x); if x = 0 then inc(cont);
      suma := suma + x;
    end;
    readln();
  end;

  n := n*n;
  sumat := (n*(n+1)) div 2;
  suma := sumat - suma;

  suma := suma*2;
  suma := suma div cont;
  suma := suma - cont + 1;
  suma := suma div 2;
  writeln(suma,' ',suma+cont-1);



  close(input);
  close(output);
end.
