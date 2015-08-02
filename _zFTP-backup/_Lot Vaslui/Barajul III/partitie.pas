var n,i,j,pas,nn,t,t2:longint;
    act:int64;
    bufout:array[1..65000]of byte;

begin
  assign(input,'partitie.in'); reset(input);
  assign(output,'partitie.out'); rewrite(output);
  settextbuf(output,bufout);

  readln(n); nn:= n-1;

  for i := 2 to n-2 do
    if nn mod i = 0 then
    begin
      pas := i;
      break;
    end;

  for t := 1 to n do
  begin
    write(t,' '); i := 1; j := t; act := t;
    for t2 := 2 to n do
    begin
      inc(i); j := j + pas; act := act + n + pas;
      if j > n then
      begin
        j := j mod n; act := act - n;
      end;
      write(act,' ');
    end;  writeln();

  end;


  close(input);
  close(output);
end.
