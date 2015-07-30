type punct=record
       x,y:smallint;
     end;

var n,nr,i,t:longint;
    a:array[0..250001]of punct;
    bufin:array[1..65000]of byte;
    iesi:boolean;
    nrlmax:longint;
    ppmm,pm,nrd:longint;
    v1,v2:array[-1000..1000]of longint;
    bol:array[0..250001]of boolean;

begin
  assign(input,'puncte6.in'); reset(input);
  assign(output,'puncte6.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n);
  for i := -1000 to 1000 do
  begin
    v1[i] := 0;
    v2[i] := 0;
  end;

  for i := 1 to n do
  begin
    readln(a[i].x,a[i].y);
    inc(v1[a[i].x]);
    inc(v2[a[i].y]);
  end;

  ///////////////////////////////////////////a
  nrlmax := 0;
  for i := -1000 to 1000 do
  begin
    if nrlmax < v1[i] then nrlmax := v1[i];
    if nrlmax < v2[i] then nrlmax := v2[i];
  end;

  writeln(nrlmax);
  //////////////////////////////////////////b
  ppmm := 0; pm := 0;
  for i := 1 to n do
  begin
    if a[i].x=a[i].y then inc(ppmm)
    else
    if a[i].x+a[i].y=0 then inc(pm);
    if (a[i].x =0)and(a[i].y=0) then dec(ppmm);
  end;
  if ppmm > 0 then nrd := 1 else nrd := 0;
  if pm   > 0 then inc(nrd);
  nrd := nrd + ppmm*pm;
  writeln(nrd);
  //////////////////////////////////////////c
  t := 0; nr := n;
  for i := 1 to n do bol[i] := true;
  repeat
    for i := 1 to n do
      if bol[i]= true then
      begin
        if t = 0 then
        begin
          bol[i] := false;
          dec(nr);
          if nr = 1 then break;
        end;
        t := (t+1)mod 3;
      end;
  until nr = 1;

  for i := 1 to n do
    if bol[i] = true then t := i;

  for i := -999 to 999 do
  begin
    if v1[i] >= t then
    begin
      write(i);
      break;
    end
    else
      t := t - v1[i];
  end;


  close(input);
  close(output);
end.
