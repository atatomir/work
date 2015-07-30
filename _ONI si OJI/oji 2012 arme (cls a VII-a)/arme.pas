var f:text;
    a,b:array[1..1000]of smallint;
    c  :array[1..2000]of smallint;
    n,m,i,j,cont,h:smallint;
    iesi:boolean;
    suma:longint;


begin
  assign(f,'arme.in'); reset(f);
  readln(f,n,m);
  for i := 1 to n do read(f,a[i]);
  for i := 1 to m do read(f,b[i]);
  for i := 1 to 2000 do c[i] := 0;
  close(f);

  //write('test1');
  repeat
    iesi:= false;
    for i := 1 to n-1 do
      if a[i]<a[i+1] then
      begin
        j := a[i];
        a[i]:=a[i+1];
        a[i+1]:=j;
        iesi := true;
      end;
  until iesi = false;
  //write('test2');

  repeat
    iesi:= false;
    for i := 1 to m-1 do
      if b[i]<b[i+1] then
      begin
        j := b[i];
        b[i]:=b[i+1];
        b[i+1]:=j;
        iesi := true;
      end;
  until iesi = false;



  i := 1; j := 1; cont:=1;iesi := false;

  repeat
    if ((i > n) or (j> m)) or (cont >n) then iesi := true
    else
    begin
      if a[i] > b[j] then
      begin
        c[cont] := a[i];
        inc(cont);
        inc(i);
      end
      else
      begin
        c[cont] := b[j];
        inc(cont);
        inc(j);
      end;
    end;
  until iesi = true;

    assign(f,'arme.out'); rewrite(f);
    suma:=0;

    for h := 1 to cont-1 do
      suma:= suma + c[h];

    if cont <= n then
      if i <= n then
        for h := i to i+n-cont do suma := suma + a[h]
      else
        for h := j to j+m-cont do suma := suma + b[h];


    write(f,suma);
    close(f);
end.
