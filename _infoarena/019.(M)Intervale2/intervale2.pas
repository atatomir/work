var n,i,x,j,cont,max,min:longint;
    a:array[1..100001]of longint;

begin
  assign(input,'intervale2.in'); reset(input);
  assign(output,'intervale2.out'); rewrite(output);

  readln(n);   max := -2000000001;  min := 2000000001;
  for i := 1 to n do read(a[i]);
  readln();

  for i := 1 to n do
  begin
    if a[i] >= max then
    begin
      max := a[i];
      write('0 ');
      read(x);
    end
    else
      if a[i] < min then
      begin
        read(x);
        min := a[i];
        write(i-x,' ');
      end
      else
      begin
        read(x);  cont := 0;
        for j := x to i-1 do
        begin
          if a[j] > a[i] then inc(cont);
        end;
        write(cont,' ');
      end;
  end;


  close(input);
  close(output);
end.