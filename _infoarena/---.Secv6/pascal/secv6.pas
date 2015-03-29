const nr=8192;
var n,i,min,x,cont,cc:longint;
    c:array[0..16000005]of longint;
    bufin:array[1..65000]of byte;
    a:array[0..nr+5]of longint;
    sum:longint;

begin
  assign(input,'secv6.in'); reset(input);
  assign(output,'secv6.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n);
  min := n ; if nr < min then min := nr;

  for i := 0 to min-1 do read(a[i]);

  c[0] := 0; sum := 0;
  for i := 0 to n-1 do
  begin
    x := i + ((a[i div nr])xor(a[i mod nr]));
    cc := c[0];
    cont := c[0];
    while (c[0] <> 0)and(x > c[c[0]]) do
    begin
      dec(cont);
      dec(c[0]);
    end;
    if cont = 0 then cont := 1;
    sum := sum+ cc - cont +1;  //writeln(sum);

    inc(c[0]);
    c[c[0]] := x;

  end;


  writeln(sum);



  close(input);
  close(output);
end.
