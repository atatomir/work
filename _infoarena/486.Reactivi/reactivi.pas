type
  temp=record
    min,max:shortint;
  end;

var bufin:array[1..65000]of byte;
    a:array[1..8001]of temp;
    n,i,cont,maxd,minim,j,loc:longint;
    ok:boolean;
    t:temp;

begin
  assign(input,'reactivi.in'); reset(input);
  assign(output,'reactivi.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n);
  for i := 1 to n do
    readln(a[i].min,a[i].max);


  {repeat               //bubble sort
    ok := true;
    for i := 1 to n-1 do
    begin
      if (a[i].min > a[i+1].min) then
      begin
        ok := false;
        t := a[i];
        a[i] := a[i+1];
        a[i+1] := t;
      end;
    end;
  until ok = true; }

  j := 0;       //select sort

  while j+1 <= n do
  begin
    inc(j);
    minim := a[j].min;  loc := j;
    for i := j+1 to n do
    begin
      if a[i].min < minim then
      begin
        minim := a[i].min;
        loc := i;
      end;
    end;

    if loc <> j then
    begin
      t := a[j];
      a[j] := a[loc];
      a[loc] := t;
    end;
  end;              // terminare select sort

  cont := 0; i := 0;

  while i+1 <= n do
  begin
    inc(i);
    maxd := a[i].max;
    while (i+1 <= n) and (a[i+1].min <= maxd) do
    begin
      inc(i);
      if a[i].max < maxd then maxd := a[i].max;
    end;
    inc(cont);
  end;

  write(cont);

  close(input);
  close(output);
end.

