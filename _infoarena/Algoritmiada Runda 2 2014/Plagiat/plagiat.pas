var t,ti:longint;
    n,i:longint;
    a:array[1..400,1..2]of longint;
    bufin:array[1..65000]of byte;

procedure Cauta;
var i1,i2,i3,i4,i5,i6,d1,d2,d3:longint;
begin
  for i1 := 1 to n-2 do
    for i2 := i1+1 to n-1 do
      for i3 := i2+1 to n do
        for i4 := i1 to n-2 do
          for i5 := i4+1 to n-1 do
            for i6 := i5+1 to n do
            begin
              d1 := a[i1,1] - a[i4,1];
              d2 := a[i2,1] - a[i5,1];
              d3 := a[i3,1] - a[i6,1];
              if (d1 = d2)and(d2=d3)and(d1<>0) then
              begin
                d1 := a[i1,2] - a[i4,2];
                d2 := a[i2,2] - a[i5,2];
                d3 := a[i3,2] - a[i6,2];
                if (d1 = d2)and(d2=d3) then
                begin
                  writeln('DA');
                  exit;
                end;
              end;
            end;



  writeln('NU');
end;

procedure Bubble;
var i,y:longint;
    iesi:boolean;
begin
  repeat
    iesi := true;
    for i := 1 to n-1 do
    begin
      if a[i,1] > a[i+1,1] then
      begin
        y := a[i,1] ; a[i,1] := a[i+1,1] ; a[i+1,1] := y;
        y := a[i,2] ; a[i,2] := a[i+1,2] ; a[i+1,2] := y;
        iesi := false;
      end
      else
      if a[i,1] = a[i+1,1] then
        if a[i,2] > a[i+1,2] then
        begin
          y := a[i,1] ; a[i,1] := a[i+1,1] ; a[i+1,1] := y;
          y := a[i,2] ; a[i,2] := a[i+1,2] ; a[i+1,2] := y;
          iesi := false;
        end;
    end;
  until iesi;
end;

begin
  assign(input,'plagiat.in'); reset(input);
  assign(output,'plagiat.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(t);
  for ti := 1 to t do
  begin
    readln(n);
    for i := 1 to n do
      readln(a[i,1],a[i,2]);

    Bubble;

    Cauta;

  end;

  close(input);
  close(output);
end.