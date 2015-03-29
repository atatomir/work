var fin,fout:text;
    //s:string;
    c:char;
    cuv:longword;
    lit,i:longword;
    sant:boolean;

begin
  assign(fin,'text.in'); reset(fin);
  cuv:=0;
  lit:=0;
  sant:=true;




  while   eof(fin)=false  do
  begin
    read(fin,c);



       if ( (c>='a') and (c<='z') ) or
       ( (c>='A') and (c<='Z') ) then
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

  //read(fin,s);
  //write('-',s,'-');

  if cuv <>0 then
    lit:= lit div cuv
  else
    lit:=0;
  close(fin);
  assign(fout,'text.out'); rewrite(fout);
  write(fout,lit);
  close(fout);
end.
