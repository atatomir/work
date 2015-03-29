const modd = 1000000007;
var n,m,x1,x2,y1,y2,ii,i,j:longint;
    hash:int64;
    v:array[0..1005,0..1005]of byte;

procedure Intersect(x1,y1,x2,y2,x3,y3,x4,y4:longint;var x,y,xx,yy,c:longint);
var xmin,ymin,xmax,ymax,i,j:longint;
begin
  c := 0;
  if x1 < x3 then xmin := x1 else xmin := x3;
  if y1 < y3 then ymin := y1 else ymin := y3;
  if x2 > x4 then xmax := x2 else xmax := x4;
  if y2 > y4 then ymax := y2 else ymax := y4;

  for i := xmin to xmax do
    for j := ymin to ymax do
      v[i,j] := 0;
  for i := x1 to x2 do
    for j := y1 to y2 do
      inc(v[i,j]);
  for i := x3 to x4 do
    for j := y3 to y4 do
      inc(v[i,j]);

  x := 0; y := 0; xx := 0; yy := 0;
  for i := x1 to x2 do
    for j := y1 to y2 do
    begin
      if v[i,j] = 2 then
      begin
        if x = 0 then
        begin
          x := i; y := j;
        end;
        xx := i; yy := j;
      end;
    end;

  if x <> 0 then
  begin
    if (x = x1)and (y = y1) then c := 1;
    if (xx = x2) and (yy = y2) then c := 3;
    //
  end;
end;

procedure Do_Hash(x,y:longint);
var t:int64;
begin
  inc(ii);
  t := (ii * x*y) mod modd;
  hash := (hash + t) mod modd;      writeln(x,y);
end;

procedure Rezolva(x1,y1,x2,y2,x3,y3,x4,y4:longint);
var x,y,xx,yy,c,i,j:longint;
begin
  Intersect(x1,y1,x2,y2,x3,y3,x4,y4,x,y,xx,yy,c);
  if c = 0 then
  begin
    for i := x1 to x2 do
      for j := y1 to y2 do
        Do_Hash(i,j);
  end
  else
  begin
    {case c of
      //1:
      //2:
      3: begin
           for i := x1 to x1+xx-x do
             for j := y1+yy-y+1 to y2 do
               Do_Hash(i,j);
           Rezolva(x1,y1,x1+xx-x,y1+yy-y,x3,y3,x4,y4);
           for i := x1+xx-x+1 to x2 do
             for j := y1 to y2 do
               Do_Hash(i,j);
         end;
     // 4:
    end;  }
  end;
end;

begin
  assign(input,'memcpy.in'); reset(input);
  assign(output,'memcpy.out'); rewrite(output);

  readln(n,m,x1,y1,x2,y2);
  hash := 0; ii := 0;

  Rezolva(x1,y1,x1+n-1,y1+m-1,x2,y2,x2+n-1,y2+m-1);

  writeln(hash);

  close(input);
  close(output);
end.
