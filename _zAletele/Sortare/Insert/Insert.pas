var bufin,bufout:array[1..65000]of byte;
    n,i,x,u,v,m,pos,j:longint;
    a:array[1..500001]of longint;
    ok:boolean;

begin
  assign(input,'algsort.in'); reset(input);
  assign(output,'algsort.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  readln(n);
  for i := 1 to n do
  begin
    read(x);

    u := 1; v := i-1;  ok := true;
    while u <= v do
    begin
      m := (u+v)div 2;
      if a[m] = x then
      begin
        pos := m+1;
        u := v + 30;
        ok := false;
      end
      else
      begin
        if a[m] > x then v := m -1 else u := m +1 ;
      end;
    end;  //end cautare binara

    if ok = true then pos := u;

    for j := i downto pos+1 do
    begin
      a[j] := a[j-1];
    end;

    a[pos] := x;

  end;



  for i := 1 to n do write(a[i],' ');

  close(input);
  close(output);
end.
