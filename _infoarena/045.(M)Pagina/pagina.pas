var n,i,j,max,t,k:longint;
    a:array[1..100001]of longint;
    s,sl,st:int64;
    iesi:boolean;

begin
  assign(input,'pagina.in'); reset(input);
  assign(output,'pagina.out'); rewrite(output);

  readln(n);   max := -1; s := 0;
  for i := 1 to n do
  begin
    read(a[i]);
    s := s + a[i];
    if max < a[i] then max := a[i];
  end;

  sl := 0; t := 0;

  while sl < max do
  begin
    inc(t);
    sl := sl + a[t];
  end;
  sl := sl - a[t];

  for i := t to n do
  begin
    sl := sl + a[i];
    if s mod sl = 0 then
    begin
      k := i+1; st := 0; iesi := false;
      for j := k to n do
      begin
        st := st + a[j];
        if st = sl then
          st := 0
        else
          if st > sl then
          begin
            iesi := true;
            break;
          end;
      end;
      if iesi = false then
      begin
        write(sl);
        exit;
      end;
    end;

  end;



  close(input);
  close(output);
end.