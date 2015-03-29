var n,i,t,ti,opp,x,y:longint;
    a:array[0..100001]of longint;
    bufin,bufout:array[1..65000]of byte;
    pos:longint;
    rez,max:longint;
 
begin
  assign(input,'kami.in'); reset(input);
  assign(output,'kami.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);
 
  readln(n); max := 0;
  for i := 1 to n do
  begin
    read(a[i]);
    if max < a[i] then max := a[i];
  end;
 
  readln();
 
  readln(t);  a[0] := 1000000005;
  for ti := 1 to t do
  begin
    read(opp);
    if opp = 0 then
    begin
      readln(x,y);
      a[x] := y;
    end
    else
    begin
      read(pos);
      rez := a[pos];
      dec(pos);
      while rez > a[pos] do
      begin
        rez := rez + a[pos];
        if rez > max then
        begin
          pos := 0;
          break;
        end;
        dec(pos);
      end;
 
      writeln(pos);
    end;
  end;
 
 
 
  close(input);
  close(output);
end.