var n,i,j,t,max,min:longint;
    a,st:array[0..50005]of longint;
    bufin:array[1..65000]of byte;
    ok:boolean;


begin
  assign(input,'stiva3.in'); reset(input);
  assign(output,'stiva3.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n);
  for t := 1 to 5 do
  begin
    min := 1 shl 30;
    for i := 1 to n do
    begin
      read(a[i]);
      if min > a[i] then min := a[i];
    end; readln();

    min := min-1;
    for i := 1 to n do a[i] := a[i] - min;

    st[0] := 0; max := 0; ok := true;
    for i := 1 to n do
    begin
      if a[i] > max then
      begin
        for j := max+1 to a[i]-1 do
        begin
          inc(st[0]);
          st[st[0]] := j;
        end;
        max := a[i];
      end
      else
      begin
        if st[0] > 0 then
        begin
          if st[st[0]] = a[i] then
          begin
            dec(st[0]);
          end
          else
          begin
            ok := false;
            break;
          end;
        end
        else
        begin
          ok := false;
          break;
        end;

      end;

    end;

    if ok then writeln(1) else writeln(0);
  end;



  close(input);
  close(output);
end.
