program Monthly_Paranteze2;

var fin,fo:text;
    c:char;
    p:longint;
    s,lz,i:longint;
    str:Array[1..1000000] of char;
    s1:ansistring;
    bufin:array[1..65000] of byte;


begin
  assign(fin,'paranteze2.in'); reset(fin);
  settextbuf(fin,bufin);
  s :=0; p :=0; lz:=0;i:=1;
  s1 := '';
  readln(fin,s1);

  {
 repeat

   readln(fin,s1);
   inc(i);
  until ( EOF(fin)=true) ;
         }

  {
  while not eof(fin) do
  begin
    read(fin,c);
    if c ='(' then  inc(p);
    if c =')' then
     begin
      if p > 0 then
      begin
        p := p-1;
        if p = 0 then
        begin
          s := s + 1 + lz;
          lz := lz + 1;
        end
        else
          s := s+1;
      end;
    end;

  end;
   }



  close(fin);
  assign(fo,'paranteze2.out'); rewrite(fo);
  write(fo,length(s1));
  close(fo);
end.
