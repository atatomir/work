var f,fo:text;
    n,i,j,t,flm:smallint;
    m,x:longint;
    a:array[1..10000]of longint;
    buff:array[1..65000]of byte;
    iesit:boolean;
    s:int64;
    sortat,gata:boolean;

begin
  assign(f,'filme.in'); reset(f);
  assign(fo,'filme.out'); rewrite(fo);
  settextbuf(f,buff);
  readln(f,n,m);
  s:=0;
  for i := 1 to n do
  begin
    readln(f,a[i],x);
    a[i] := a[i] + x;
    s := s + a[i];
  end;

  if s < m then write(fo,n)
  else
  begin
    s :=0; flm :=0;

    i :=n-1; iesit:=false;  sortat := false;
    repeat
      if sortat = false then
      begin
        gata := false;
        for j := 1 to i do
        begin
          if a[j] < a[j+1] then
          begin
            t:=a[j];
            a[j]:=a[j+1];
            a[j+1] := t;
            gata := true;
          end;
        end;
        if gata = false then sortat := true;
      end;
      if s+a[i+1]<= m then
      begin
      s := s + a[i+1];
      inc(flm);
      end else iesit := true;
      i := i-1;

    until (iesit=true) or (i=0)or (sortat=true);
    if s < m then
    begin
      while (i > 0)and(iesit=false) do
      begin
        if s+a[i+1]<= m then
        begin
        s := s + a[i+1];
        inc(flm);
        end else iesit := true;
        i := i-1;
      end;
    end;
    write(fo,flm);
  end;
  close(f);
  close(fo);
end.
