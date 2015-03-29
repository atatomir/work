var fin,fout:text;
    s:string;
    cuv:longword;
    lit,l,i:longword;
    sant:boolean;

begin
  assign(fin,'text.in'); reset(fin);
  cuv:=0;
  lit:=0;
  sant:=true;

  read(fin,s);
  while  {eof(fin)=false} s<>'' do
  begin
    l:= length(s);
    //writeln(l);
    for i := 1 to l do
    begin
      //write(s[i]);
      if ( (s[i]>='a') and (s[i]<='z') ) or
         ( (s[i]>='A') and (s[i]<='Z') ) then
      begin
        inc(lit);
        if sant = true then
        begin
          inc(cuv);
          sant:=false;
        end;
      end
      else
        sant:=true;
    end;
    //write('-',lit);
    read(fin,s);
  end;

  if cuv <>0 then
    lit:= lit div cuv
  else
    lit:=0;
  close(fin);
  assign(fout,'text.out'); rewrite(fout);
  write(fout,lit);
  close(fout);
end.
