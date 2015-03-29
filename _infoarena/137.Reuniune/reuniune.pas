program reuniune;

type dreptunghi=record
  x1,y1,x2,y2:int64;
end;

var A,P:int64;
    f,fo:text;
    d:array[1..3]of dreptunghi;
    d12,d13,d23,d123:dreptunghi;

procedure intersect(d1,d2:dreptunghi;var di:dreptunghi);
var xm,ym,xm2,ym2:int64;
begin
  di.x1:=0;di.x2:=0;di.y1:=0;di.y2:=0;
  if d1.x1 < d2.x1 then xm := d2.x1 else xm := d1.x1;
  if d1.x2 < d2.x2 then xm2 := d1.x2 else xm2 := d2.x2;
  if d1.y1 < d2.y1 then ym := d2.y1 else ym := d1.y1;
  if d1.y2 < d2.y2 then ym2 := d1.y2 else ym2 := d2.y2;

  if (xm <= xm2) and (ym <= ym2) then
  begin
    di.x1 := xm;
    di.x2 := xm2;
    di.y1 := ym;
    di.y2 := ym2;
  end;
end;

function arie(d:dreptunghi):int64;
begin
  arie := (d.x2-d.x1)*(d.y2-d.y1);
end;

function perimetru(d:dreptunghi):int64;
begin
  perimetru := (d.x2 - d.x1)*2 + (d.y2 - d.y1)*2;
end;

begin
  assign(f,'reuniune.in'); reset(f);
  readln(f,d[1].x1,d[1].y1,d[1].x2,d[1].y2);
  readln(f,d[2].x1,d[2].y1,d[2].x2,d[2].y2);
  readln(f,d[3].x1,d[3].y1,d[3].x2,d[3].y2);
  close(f);

  intersect(d[1],d[2],d12);
  intersect(d[1],d[3],d13);
  intersect(d[2],d[3],d23);
  intersect(d12,d[3],d123);

  A := arie(d[1]) + arie(d[2]) + arie(d[3])
      -arie(d12)  - arie(d13)  - arie(d23)
      +arie(d123);

  P := perimetru(d[1]) + perimetru(d[2]) + perimetru(d[3])
      -perimetru(d12)  - perimetru(d13)  - perimetru(d23)
      +perimetru(d123);

  assign(fo,'reuniune.out'); rewrite(fo);
  writeln(fo,A,' ',P);
  close(fo);

end.
