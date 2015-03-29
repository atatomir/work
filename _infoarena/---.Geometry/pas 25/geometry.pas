type segment=record
       x1,x2,y1,y2:smallint;
     end;
var n,i,j:longint;
    a:array[1..500]of segment;
    bufin:array[1..65000]of byte;
    cont:longint;


function verif(i,j:longint):boolean;
var a1,a2,b1,b2,x,y:real;
begin
  verif := false;

  if (a[i].x2 < a[j].x1)or(a[i].x1 > a[j].x2)or
     (a[i].y2 < a[j].y1)or(a[i].y1 > a[j].y2) then exit;


  if (a[i].x1 = a[i].x2) or (a[j].x1 = a[j].x2) then
  begin
    verif := true;
    exit;
  end;

  a1 := (a[i].y2-a[i].y1)/(a[i].x2-a[i].x1);
  b1 := a[i].y1 - a1*a[i].x1;

  a2 := (a[j].y2-a[j].y1)/(a[j].x2-a[j].x1);
  b2 := a[j].y1 - a2*a[j].x1;

  if a1 = a2 then
  begin
    if b1 = b2 then verif := true;
    exit;
  end;

  x := (b2-b1)/(a1-a2);
  y := a1*x+b1;

  if (x>=a[i].x1) and (x<=a[i].x2) and
     (x>=a[j].x1) and (x<=a[j].x2) then
    verif := true;

end;

begin
  assign(input,'geometry.in'); reset(input);
  assign(output,'geometry.out'); rewrite(output);
  settextbuf(Input,bufin);

  readln(n);
  for i := 1 to n do readln(a[i].x1,a[i].y1,a[i].x2,a[i].y2);
  cont := 0;


  for i := 1 to n-1 do
    for j := i+1 to n do
    begin
      if verif(i,j) then
      begin
        inc(cont);
      end;
    end;

  writeln(cont);

  close(input);
  close(output);
end.