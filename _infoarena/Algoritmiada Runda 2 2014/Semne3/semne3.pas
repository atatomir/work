var n,i,t:longint;
    a:array[0..500001]of longint;
    c:array[0..500001]of char;
    bufin,bufout:array[1..65000]of byte;
    iesi:boolean;
begin
  assign(input,'semne3.in'); reset(input);
  assign(output,'semne3.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  readln(n);
  for i := 1 to n do a[i] := i;
  for i := 1 to n-1 do read(c[i]);

  repeat
    iesi := true;
    for i := 1 to n-1 do
    begin
      if c[i] = '<' then
      begin
        if a[i] > a[i+1] then
        begin
          t := a[i];
          a[i] := a[i+1];
          a[i+1] := t;
          iesi := false;
        end;
      end
      else
      begin
        if a[i] < a[i+1] then
        begin
          t := a[i];
          a[i] := a[i+1];
          a[i+1] := t;
          iesi := false;
        end;
      end;

    end;


  until iesi ;

  for i := 1 to n do write(a[i],' ');


  close(input);
  close(output);
end.
