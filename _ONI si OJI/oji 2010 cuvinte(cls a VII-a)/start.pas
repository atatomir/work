type cuvant=record
     folos:boolean;
     x:string[10];
end;

var a:array[1..25] of cuvant;
    cuv:string[10];
    deriv:string[10];
    chr:char;
    f,fo:text;
    j,i,l:byte;
    primu,gasit:boolean;


begin

  assign(f,'cuvinte.in'); reset(f);
  assign(fo,'cuvinte.out'); rewrite(fo);
  j:= 1;
  primu:= true;
  read(f,chr);

  repeat

    if chr = ' ' then
    begin
      a[j].x := cuv;
      a[j].folos := true;
      cuv := '';
      inc(j);
    end
    else
      cuv := cuv + chr;

    read(f,chr);
  until chr = '!' ;

  j := j - 1;
  i := 1;
  cuv := a[1].x;
  repeat
    if a[i].folos = false then
    begin
    end
    else
    begin
       gasit:= false;
       deriv := cuv;
       for l:= 1 to length(a[i].x)-1 do
       begin
          chr := deriv[1];
          //writeln(chr);
          //writeln(deriv);
          delete(deriv,1,1);
          //writeln(deriv);
          deriv:= deriv + chr;
          write(deriv,'-');
          writeln(a[i+1].x,'~',i);
          if deriv = a[i+1].x then
          begin
            write(' da ');
            gasit := true;
            a[i+1].folos := false;
            if primu = true then
            begin
              primu := false;
              writeln(fo,i+1);
            end;
            break;
          end;
       end;
    end;

    if gasit = false then
    begin
      cuv := a[i+1].x;
    end;

    inc(i);
    until i = j;

    i:= 1;
    repeat

       if a[i].folos=true then
       write(fo,i,' ');

      inc(i);
    until i = j + 1;



  close(f);
  close(fo);
end.
