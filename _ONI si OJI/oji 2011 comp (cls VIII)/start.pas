var f,fo:text;
    s:string[250];
    s1,s2:longint;
    a:array[1..1000] of boolean;
    n,i,loc,maiputin:word;
    chr:byte;
    trecut:boolean;
    semn:char;

begin
  assign(f,'comp.in'); reset(f);
  assign(fo,'comp.out'); rewrite(fo);

  readln(f,n);

  for i := 1 to n do
  begin

    readln(f,s);
    chr:= 1;
    trecut:= false;
    loc:= 0;
    s1:= 0;
    s2:= 0;

    repeat

      if pos(s[chr],'0123456789') > 0 then
      begin
        loc := loc*10 + ( ord(s[chr]) - $30 );
        //writeln(loc);
        //writeln(s[chr]);
        //writeln('//////');
      end
      else
      begin
         case s[chr] of
         'm': if trecut= true then
              begin
                  s2:= s2 + (loc* 1000);
                  loc:= 0;
              end
              else
              begin
                  s1 := s1 + (loc*1000);
                  loc:= 0;
              end;
         's': if trecut = true then
              begin
                  s2:= s2 + ( loc*100);
                  loc:= 0;
              end
              else
              begin
                  s1 := s1 + (loc*100);
                  loc:= 0;
              end;
         'z': if trecut = true then
              begin
                  s2 := s2 + (loc*10);
                  loc:= 0;
              end
              else
              begin
                s1:= s1 + (loc*10);
                loc:= 0;
              end;
         'u': if trecut = true then
              begin
                s2 := s2 + loc;
                loc:=0;
              end
              else
              begin
                s1:= s1 + loc;
                loc:=0;
              end;

         '>': begin
                trecut := true;
                semn:= s[chr];
                loc:=0
              end;
         '<': begin
                trecut := true;
                semn := s[chr];
                inc(maiputin);
                loc:=0
              end;


         end;
      end;


      inc(chr);
    until chr = length(s)+1;

    //writeln('------------');
   // writeln(s1,'-',s2);

    if ( ( s1 > s2) and (semn = '>') ) or ( ( s1 < s2) and (semn = '<') ) then
      a[i] := true
    else
      a[i] := false;

  end;

  writeln(fo,maiputin);

  for i := 1 to n do
  begin
     if a[i] = false then
       writeln(fo,'0')
     else
       writeln(fo,'1');
  end;





  close(fo);
  close(f);
end.
