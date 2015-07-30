var bufin,bufout:array[1..65000]of byte;
    c,d,i,j:longint;
    a:array[1..100003]of longint;
    x,rest,min:longint;
    zero:boolean;

begin
  assign(input,'alune.in'); reset(input);
  assign(output,'alune.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  readln(c,d);       min := 999999999;
  for i := 1 to c do
  begin
    read(a[i]);
    if min > a[i] then min := a[i];
  end;
  readln();

  for i := 1 to d do
  begin
    read(x);
    if x < min then
    begin
      write('1') ;
    end
    else
    begin
      zero := false;
      rest := x mod a[1];
      for j := 2 to c do
        if x mod a[j] <> rest then
        begin
          zero := true;
          break;
        end;

      if zero = true then write('0') else write('1');
    end;
  end;

  close(input);
  close(output);
end.
