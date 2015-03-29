program Muzeu;

const max=10000;

var n:integer;
    f,fo:text;
    a:array[1..2,1..250,1..250]of longint;
    i,j,l:longint;
    c:char;
    msc:boolean;

begin
  assign(f,'muzeu.in'); reset(f);
  readln(f,n);
  for i := 1 to n do
  begin
    for j := 1 to n do
    begin
      read(f,c);
      case c of
        'P': a[1,i,j] := 0;
        '.': a[1,i,j] := max;
        '#': a[1,i,j] := -2;
      end;
    end;
    readln(f);
  end;

  for i := 1 to n do
    for j := 1 to n do
    begin
      if a[1,i,j]=0 then
      begin
        if i<>1 then
          if a[1,i-1,j] <> -2 then a[1,i-1,j] := 1;
        if i<>n then
          if a[1,i+1,j] <> -2 then a[1,i+1,j] := 1;
        if j<>1 then
          if a[1,i,j-1] <> -2 then a[1,i,j-1] := 1;
        if j<>n then
          if a[1,i,j+1] <> -2 then a[1,i,j+1] := 1;
      end;
    end;

    for i := 1 to n do
      for j := 1 to n do
        a[2,i,j] := a[1,i,j];

  repeat
    msc:=false;
    for i := 1 to n do
      for j := 1 to n do
      begin
        if (a[1,i,j] > 0)and(a[1,i,j]<>max) then
        begin
        if i<>1 then
          if (a[1,i-1,j] <> -2) and (a[1,i,j]+1 < a[2,i-1,j]) then begin a[2,i-1,j] := a[1,i,j]+1; msc := true; end;
        if i<>n then
          if (a[1,i+1,j] <> -2) and (a[1,i,j]+1 < a[2,i+1,j]) then begin a[2,i+1,j] := a[1,i,j]+1; msc := true; end;

        if j<>1 then
          if (a[1,i,j-1] <> -2) and (a[1,i,j]+1 < a[2,i,j-1]) then begin a[2,i,j-1] := a[1,i,j]+1; msc := true; end;
        if j<>n then
          if (a[1,i,j+1] <> -2) and (a[1,i,j]+1 < a[2,i,j+1]) then begin a[2,i,j+1] := a[1,i,j]+1; msc := true; end;

        end;
      end;

    for i := 1 to n do
      for j := 1 to n do
        a[1,i,j] := a[2,i,j];

  until msc = false;



  for i := 1 to n do
    for j := 1 to n do
      if a[1,i,j] = max then a[1,i,j] := -1;



  assign(fo,'muzeu.out'); rewrite(fo);
  for i := 1 to n do
  begin
    for j := 1 to n do
      write(fo,a[1,i,j],' ');
    writeln(fo);
  end;
  close(fo);
end.
