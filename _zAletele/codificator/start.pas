var fin,fout:text;
    dcod:string;
    i: integer;
    cod:char;


begin

assign(fin,'fin.bin'); reset(fin);
assign(fout,'fout.bin'); rewrite(fout);
read(fin,dcod);
 for i := 1 to length(dcod) do
 begin
 cod := succ(dcod[i]);
 write(fout,cod);
 end;



close(fout);
close(fin);
end.
