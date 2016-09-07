void TUNLStyle()
{
  
  //..TUNL styles
  //TStyle *tunlStyle= new TStyle("TUNL","style file for TUNL plots");
  
  gStyle->SetAxisColor(1, "xyz");
  
  gStyle->SetLabelColor(1, "xyz");
  gStyle->SetLabelFont(132, "xyz");
  gStyle->SetLabelOffset(0.013, "xyz");
  gStyle->SetLabelSize(0.05, "xyz");
  
  gStyle->SetTickLength(0.03, "xyz");
  
  gStyle->SetTitleOffset(1.02, "x");
  gStyle->SetTitleOffset(1.28, "y");
  gStyle->SetTitleOffset(1.15, "z");
  gStyle->SetTitleSize(0.06, "xyz");
  gStyle->SetTitleColor(1, "xyz");
  gStyle->SetTitleFont(132, "xyz");
  
  
  gStyle->SetDrawBorder(0);
  
  gStyle->SetOptLogx(0);
  gStyle->SetOptLogy(0);
  gStyle->SetOptLogz(0);
  
  gStyle->SetOptTitle(kFALSE);
  
  gStyle->GetAttDate()->SetTextFont(132);
  gStyle->GetAttDate()->SetTextSize(0.05);
  gStyle->GetAttDate()->SetTextAngle(1);
  gStyle->GetAttDate()->SetTextAlign(11);
  gStyle->GetAttDate()->SetTextColor(15);
  gStyle->SetDateX(0.02);
  gStyle->SetDateY(0.02);
  
  
  gStyle->SetFuncColor(1);
  gStyle->SetFuncStyle(1);
  gStyle->SetFuncWidth(2);
  
  gStyle->SetGridColor(1);
  gStyle->SetGridStyle(3);
  gStyle->SetGridWidth(1);
  
  gStyle->SetHistFillColor(0);
  gStyle->SetHistLineColor(1);
  gStyle->SetHistFillStyle(1001);
  gStyle->SetHistLineStyle(1);
  gStyle->SetHistLineWidth(1);
  //gStyle->SetHistMinimumZero(kFALSE);
  
  gStyle->SetCanvasColor(0);
  gStyle->SetCanvasBorderSize(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetCanvasDefH(500);
  gStyle->SetCanvasDefW(640);
  gStyle->SetCanvasDefX(10);
  gStyle->SetCanvasDefY(10);

  
  gStyle->SetFrameFillColor(0);
  gStyle->SetFrameLineColor(1);
  gStyle->SetFrameFillStyle(1001);
  gStyle->SetFrameLineStyle(1);
  gStyle->SetFrameLineWidth(1);
  gStyle->SetFrameBorderSize(1);
  gStyle->SetFrameBorderMode(0);
  
  gStyle->SetPadColor(0);
  gStyle->SetPadBorderSize(1);
  gStyle->SetPadBorderMode(0);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadTopMargin(0.06);
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.065);
  gStyle->SetPadGridX(kFALSE);
  gStyle->SetPadGridY(kFALSE);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  
  //gStyle->SetPaperSize(20, 26);
  //gStyle->SetScreenFactor(1);
  
  
  gStyle->SetOptStat(1002210);
  gStyle->SetStatColor(0);
  gStyle->SetStatTextColor(1);
  gStyle->SetStatBorderSize(0);
  gStyle->SetStatFont(132);
  gStyle->SetStatFontSize(0.048);
  gStyle->SetStatStyle(1001);
  gStyle->SetStatFormat("6.4g");
  gStyle->SetStatX(0.909516);
  gStyle->SetStatY(0.922043);
  gStyle->SetStatW(0.340726);
  gStyle->SetStatH(0.27957);
  
  //gStyle->SetFitFormat("5.4g");
  
  
  
  gStyle->SetStripDecimals(kTRUE);
  
  gStyle->SetTitleAlign(13);
  gStyle->SetTitleFillColor(0);
  gStyle->SetTitleTextColor(1);
  gStyle->SetTitleBorderSize(1);
  gStyle->SetTitleFont(132);
  gStyle->SetTitleFontSize(0.06);
  gStyle->SetTitleStyle(1001);
  gStyle->SetTitleX(0.01);
  gStyle->SetTitleY(0.995);
  gStyle->SetTitleW(0);
  gStyle->SetTitleH(0);
  
  gStyle->SetPaintTextFormat("g");
  // gStyle->SetLineScalePS(3);
  //gStyle->SetColorModelPS(0);
  gStyle->SetTimeOffset(788918400);
  
  gStyle->SetLineColor(1);
  gStyle->SetLineStyle(1);
  gStyle->SetLineWidth(1);
  //gStyle->SetFillColor(0);
  gStyle->SetFillStyle(1001);
  gStyle->SetMarkerColor(1);
  gStyle->SetMarkerSize(0.7);
  gStyle->SetMarkerStyle(10);
  gStyle->SetTextAlign(11);
  gStyle->SetTextAngle(0);
  gStyle->SetTextColor(1);
  gStyle->SetTextFont(132);
  gStyle->SetTextSize(0.05);
}
