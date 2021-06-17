{
  Det_Si *t = new Det_Si();
  t->Loop();

  TCanvas *c2 = new TCanvas("c2", "c2");
  h_1->SetMaximum(100.0);
  h_1->Draw();
  h_2->Draw("same");
  h_3->Draw("same");
  h_4->Draw("same");

  TLegend *legend = new TLegend();
  legend->AddEntry( h_1, "6he+p" , "l");
  legend->AddEntry( h_2, "6he+C" , "l");
  legend->AddEntry( h_3, "3h+p" , "l");
  legend->AddEntry( h_4, "3h+C" , "l");
  legend->SetFillColor(0);
  legend->SetBorderSize(0);
  legend->Draw();

  cout << "Count (100s)" << endl;
  cout << " 6he+p: " << h_1->GetEntries() << endl;
  cout << " 6he+C: " << h_2->GetEntries() << endl;
  cout << " 3h+p:  " << h_3->GetEntries() << endl;
  cout << " 3h+C:  " << h_4->GetEntries() << endl;
}
