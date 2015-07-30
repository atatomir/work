program elicoper;
type elicop=record
  susjos:boolean;
  x1,x2,y1,y2:byte;
end;

var f,fo:text;
    m,n,nr,i,j,s,gresit:byte;
    a:array[1..40] of elicop;
    c:array[1..40] of byte;
    b:array[1..100,1..100] of byte;
    zerouri,hep:integer;
    nedistrugatoare:byte;

begin
  assign(f,'elicop.in'); reset(f);
  assign(fo,'elicop.out'); rewrite(fo);

  readln(f,m,n);

  for j := 1 to m do
  begin
    for s := 1 to n do
      read(f,b[j,s]);
    readln(f);
  end;

  readln(f,nr);


  zerouri:= 0;
  nedistrugatoare := 0;
  gresit := 0;

  for i := 1 to nr do
  begin
    readln(f,a[i].y1,a[i].x1,a[i].y2,a[i].x2,hep);
    if hep = 1 then
      a[i].susjos := true
    else
      a[i].susjos := false;

    if ( a[i].x1 > a[i].x2 ) and ( a[i].susjos = true ) then
    begin
      for j := 1 to a[i].y2 - a[i].y1+1 do
        for s := 1 to j do
          if b[ a[i].y2 - j +1 , a[i].x2 + s -1 ] = 0 then
            inc(zerouri);
    end;

    if ( a[i].x1 < a[i].x2 ) and ( a[i].susjos = true ) then
    begin
      for j := 1 to a[i].y2 - a[i].y1+1 do
        for s := 1 to j do
          if b[ a[i].y2 - j +1 , a[i].x2 - s +1 ] = 0 then
            inc(zerouri);
    end;

    if ( a[i].x1 > a[i].x2 ) and ( a[i].susjos = false ) then
    begin
      for j := 1 to a[i].y2 - a[i].y1+1 do
        for s := 1 to j do
          if b[ a[i].y1 + j - 1 , a[i].x1 - s + 1 ] = 0 then
            inc(zerouri);
    end;

    if ( a[i].x1 < a[i].x2 ) and ( a[i].susjos = false ) then
    begin
      for j := 1 to a[i].y2 - a[i].y1+1 do
        for s := 1 to j do
          if b[ a[i].y1 + j -1 , a[i].x1 + s -1 ] = 0 then
            inc(zerouri);
    end;






    if zerouri = 0 then
      inc(nedistrugatoare);

    if zerouri > (((a[i].y2 - a[i].y1 + 1)*(a[i].y2-a[i].y1+2)) div 4 ) then
    begin
      inc(gresit);
      c[gresit] := i ;
    end;
    zerouri := 0;
  end;


  writeln(fo,nedistrugatoare);
  write(fo,gresit,' ');

  for i := 1 to gresit do
  write(fo,c[i],' ');












  close(f);
  close(fo);

end.
