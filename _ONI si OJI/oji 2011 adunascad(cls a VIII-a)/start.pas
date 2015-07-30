

var n,s:integer;
    m,j:byte;
    sloc,i,t:longint;
    f,fo:text;
    a:array[1..20] of byte;

begin
  assign(f,'adunascad.in'); reset(f);
  assign(fo,'adunascad.out'); rewrite(fo);
  sloc:= 1;

  readln(f,n,m);
  for i := 1 to m do
    read(f,a[i]);

  for i := 1 to m do
     sloc := sloc * 2;

  //writeln(fo,sloc);

  for i := 0 to sloc-1 do
  begin
    s:= 0; t := 1;
    for j := 0 to m-1 do
    begin
   // writeln(fo,i and t);
   // writeln(fo,i,' ',t);
      if (i and t ) > 0 then
        s := s + a[j+1]
      else
        s := s - a[j+1];
      t := t * 2;
    end;

    //writeln(fo,s,' ',n);

    if s = n then
    begin
      t:= 1;
      for j := 0 to m-1 do
      begin
        if ( i and t ) > 0 then
            write(fo,'+ ',a[j+1])
        else
          write(fo,'- ',a[j+1]);
        t := t * 2;
      end;
      writeln(fo);

    end;

  end;

   //write(fo,0);

  close(f);
  close(fo);
end.
