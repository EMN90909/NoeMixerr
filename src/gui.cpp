#include "noemix/core.hpp"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QLabel>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QPushButton>
#include <QtCore/QSignalBlocker>
#include <QtCore/QTemporaryDir>
#include <QtCore/QUrl>
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QAudioOutput>
#include <algorithm>
#include <functional>
#include <memory>

namespace {
const QColor base("#10151e"), panel("#1a2533"), ink("#e5edf7"), muted("#354459"), accent("#ff9644"),cyan("#54c3d3");
constexpr int beat_px=34,lane_px=62,track_px=155;
class Arrangement : public QWidget {
public:
 noemix::Project* project=nullptr;
 int selected=0;
 std::function<void(int)> select_track;
 std::function<void()> changed;
 Arrangement(){setMinimumWidth(track_px+beat_px*96);setMinimumHeight(400);}
protected:
 void paintEvent(QPaintEvent*) override{
  QPainter p(this);p.fillRect(rect(),base);if(!project)return;
  p.setPen(ink);p.drawText(12,23,"NOEMIXERR  /  ARRANGEMENT");
  for(int b=0;b<96;++b){const int x=track_px+b*beat_px;p.setPen(b%4==0?QColor("#526079"):muted);p.drawLine(x,32,x,height());if(b%4==0){p.setPen(ink);p.drawText(x+5,24,QString::number(b/4+1));}}
  for(int row=0;row<int(project->tracks.size());++row){
   const auto& t=project->tracks[size_t(row)];int y=34+row*lane_px;
   p.fillRect(0,y,width(),lane_px-2,row==selected?QColor("#23344a"):QColor("#16202c"));
   p.fillRect(0,y,track_px-2,lane_px-2,panel);
   p.setPen(row==selected?accent:ink);p.drawText(10,y+24,QString::fromStdString(t.name).left(20));
   p.setPen(QColor("#93a4b9"));p.drawText(10,y+45,QString("%1 MIDI  %2 audio").arg(t.notes.size()).arg(t.clips.size()));
   for(const auto& n:t.notes){QRect r(track_px+int(n.beat*beat_px),y+8,std::max(3,int(n.length*beat_px)),15);p.fillRect(r,accent);}
   for(const auto& c:t.clips){const double bars=double(c.pcm.size()/size_t(c.channels))/c.sample_rate*project->bpm/60;
    QRect r(track_px+int(c.beat*beat_px),y+33,std::max(4,int(bars*beat_px)),20);
    p.fillRect(r,cyan);p.setPen(QColor("#082a37"));p.drawText(r.adjusted(4,0,-4,0),Qt::AlignVCenter,QString::fromStdString(c.path).section('/',-1));}
  }
 }
 void mousePressEvent(QMouseEvent* e) override{
  int row=int((e->position().y()-34)/lane_px);
  if(!project||e->position().y()<34||row<0||row>=int(project->tracks.size()))return;
  selected=row;if(select_track)select_track(row);update();
 }
 void mouseDoubleClickEvent(QMouseEvent* e)override{
  if(!project||e->position().x()<track_px||e->position().y()<34)return;
  int row=int((e->position().y()-34)/lane_px);
  if(row<0||row>=int(project->tracks.size()))return;
  double beat=std::max(0.,std::floor((e->position().x()-track_px)/beat_px*2.)/2.);
  project->tracks[size_t(row)].notes.push_back({60,beat,0.5f,0.8f});
  selected=row;if(select_track)select_track(row);if(changed)changed();update();
 }
};
class PianoRoll : public QWidget{
public:
 noemix::Project* project=nullptr;
 int selected=0;
 std::function<void()> changed;
 PianoRoll(){setMinimumSize(1150,37*16);}
protected:
 void paintEvent(QPaintEvent*)override{
  QPainter p(this);p.fillRect(rect(),base);
  constexpr int key=58,step=15;
  for(int pitch=84;pitch>=48;--pitch){
   int y=(84-pitch)*step;
   int tone=pitch%12;bool sharp=tone==1||tone==3||tone==6||tone==8||tone==10;
   p.fillRect(0,y,width(),step-1,sharp?QColor("#1a2636"):QColor("#263449"));
   p.fillRect(0,y,key-1,step-1,sharp?QColor("#3d4d63"):QColor("#bdcbe0"));
   if(tone==0){p.setPen(base);p.drawText(4,y+11,QString("C%1").arg(pitch/12-1));}
  }
  for(int b=0;b<64;++b){int x=key+b*beat_px;p.setPen(b%4==0?QColor("#59708a"):muted);p.drawLine(x,0,x,height());}
  if(!project||selected<0||selected>=int(project->tracks.size()))return;
  for(const auto& n:project->tracks[size_t(selected)].notes){
   if(n.pitch<48||n.pitch>84)continue;
   QRect r(key+int(n.beat*beat_px),(84-n.pitch)*step,std::max(3,int(n.length*beat_px)),step-2);
   p.fillRect(r,accent);p.setPen(QColor("#693d1e"));p.drawRect(r);
  }
 }
 void mouseDoubleClickEvent(QMouseEvent* e)override{
  if(!project||selected<0||selected>=int(project->tracks.size())||e->position().x()<58)return;
  int pitch=84-int(e->position().y()/15);if(pitch<48||pitch>84)return;
  double beat=std::max(0.,std::floor((e->position().x()-58)/beat_px*2.)/2.);
  project->tracks[size_t(selected)].notes.push_back({pitch,beat,0.5f,0.8f});
  if(changed)changed();update();
 }
 void mousePressEvent(QMouseEvent* e)override{
  if(e->button()!=Qt::RightButton||!project||selected<0||selected>=int(project->tracks.size()))return;
  int pitch=84-int(e->position().y()/15);double beat=(e->position().x()-58)/beat_px;
  auto& notes=project->tracks[size_t(selected)].notes;
  auto it=std::find_if(notes.begin(),notes.end(),[&](const noemix::Note& n){return n.pitch==pitch&&beat>=n.beat&&beat<n.beat+n.length;});
  if(it!=notes.end()){notes.erase(it);if(changed)changed();update();}
 }
};
class Workstation : public QMainWindow{
 noemix::Project project_=noemix::demo_project();
 QString filename_;
 int selected_=0;
 Arrangement* arrangement_=nullptr;
 PianoRoll* piano_=nullptr;
 QTreeWidget* tree_=nullptr;
 QTableWidget* mixer_=nullptr;
 QDoubleSpinBox* tempo_=nullptr;
 QMediaPlayer player_;
 QAudioOutput output_;
 QTemporaryDir temp_;
public:
 Workstation(){
  setWindowTitle("NoeMixerr | Native DAW");resize(1460,900);
  setStyleSheet("QWidget{background:#10151e;color:#e5edf7;} QTreeWidget,QTableWidget,QDoubleSpinBox{background:#1a2533;color:#e5edf7;border:1px solid #354459;} QToolBar,QStatusBar{background:#1a2533;} QHeaderView::section{background:#28384a;color:white;padding:5px;}");
  player_.setAudioOutput(&output_);output_.setVolume(0.8);
  auto* toolbar=addToolBar("Session");toolbar->setMovable(false);
  auto add=[&](QString name,std::function<void()> callback){auto* action=toolbar->addAction(name);connect(action,&QAction::triggered,this,[callback]{callback();});};
  add("New",[this]{stop();project_={};project_.tracks.push_back(noemix::Track{});filename_.clear();selected_=0;refresh();});
  add("Open",[this]{open();});add("Save",[this]{save();});
  add("+ Track",[this]{auto t=noemix::Track{};t.name="Track "+std::to_string(project_.tracks.size()+1);project_.tracks.push_back(t);selected_=int(project_.tracks.size())-1;refresh();});
  add("+ WAV",[this]{importAudio();});add("Export WAV",[this]{exportAudio();});
  toolbar->addSeparator();add("▶ Play",[this]{play();});add("■ Stop",[this]{stop();});
  toolbar->addSeparator();toolbar->addWidget(new QLabel(" BPM ",this));
  tempo_=new QDoubleSpinBox;tempo_->setRange(20,400);tempo_->setDecimals(1);toolbar->addWidget(tempo_);
  connect(tempo_,qOverload<double>(&QDoubleSpinBox::valueChanged),this,[this](double v){project_.bpm=v;arrangement_->update();});
  auto* splitter=new QSplitter(Qt::Vertical,this);
  auto* upper=new QSplitter(Qt::Horizontal,splitter);
  tree_=new QTreeWidget;tree_->setHeaderLabel("TRACKS");tree_->setMinimumWidth(190);upper->addWidget(tree_);
  auto* arrangementScroll=new QScrollArea;arrangement_=new Arrangement;arrangement_->project=&project_;arrangementScroll->setWidget(arrangement_);
  upper->addWidget(arrangementScroll);upper->setStretchFactor(1,5);
  auto* lower=new QSplitter(Qt::Horizontal,splitter);
  auto* rollScroll=new QScrollArea;piano_=new PianoRoll;piano_->project=&project_;rollScroll->setWidget(piano_);lower->addWidget(rollScroll);
  mixer_=new QTableWidget;mixer_->setColumnCount(6);mixer_->setHorizontalHeaderLabels({"Track","Gain","Pan","Mute","Solo","Wave"});
  mixer_->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);mixer_->setMinimumWidth(445);lower->addWidget(mixer_);lower->setStretchFactor(0,3);
  splitter->setStretchFactor(0,3);splitter->setStretchFactor(1,2);setCentralWidget(splitter);
  arrangement_->select_track=[this](int i){select(i);};arrangement_->changed=[this]{refresh();};
  piano_->changed=[this]{refresh();};
  connect(tree_,&QTreeWidget::currentItemChanged,this,[this](QTreeWidgetItem* item){if(item)select(tree_->indexOfTopLevelItem(item));});
  connect(mixer_,&QTableWidget::cellChanged,this,[this](int row,int col){
   if(row<0||row>=int(project_.tracks.size()))return;
   auto* cell=mixer_->item(row,col);if(!cell)return;auto& t=project_.tracks[size_t(row)];
   if(col==0)t.name=cell->text().toStdString();
   if(col==1)t.gain=std::clamp(cell->text().toDouble(),0.,4.);
   if(col==2)t.pan=std::clamp(cell->text().toDouble(),-1.,1.);
   if(col==3)t.mute=cell->checkState()==Qt::Checked;
   if(col==4)t.solo=cell->checkState()==Qt::Checked;
   if(col==5)t.waveform=std::clamp(cell->text().toInt(),0,1);
   arrangement_->update();
  });
  statusBar()->showMessage("Double-click to add notes. Right-click piano roll to remove notes.");refresh();
 }
private:
 void safe(const std::function<void()>& run){try{run();}catch(const std::exception& e){QMessageBox::critical(this,"NoeMixerr",e.what());}}
 void stop(){player_.stop();}
 void select(int i){if(i<0||i>=int(project_.tracks.size()))return;selected_=i;arrangement_->selected=i;piano_->selected=i;arrangement_->update();piano_->update();}
 void refresh(){
  selected_=std::clamp(selected_,0,std::max(0,int(project_.tracks.size())-1));
  {QSignalBlocker block(tree_);tree_->clear();for(const auto& t:project_.tracks)tree_->addTopLevelItem(new QTreeWidgetItem({QString::fromStdString(t.name)}));if(!project_.tracks.empty())tree_->setCurrentItem(tree_->topLevelItem(selected_));}
  {QSignalBlocker block(mixer_);mixer_->setRowCount(int(project_.tracks.size()));
   for(int i=0;i<int(project_.tracks.size());++i){
    const auto& t=project_.tracks[size_t(i)];
    QString vals[]={QString::fromStdString(t.name),QString::number(t.gain,'f',2),QString::number(t.pan,'f',2),"","",QString::number(t.waveform)};
    for(int col=0;col<6;++col){auto* item=new QTableWidgetItem(vals[col]);if(col==3||col==4){item->setFlags((item->flags()&~Qt::ItemIsEditable)|Qt::ItemIsUserCheckable);item->setCheckState((col==3?t.mute:t.solo)?Qt::Checked:Qt::Unchecked);}mixer_->setItem(i,col,item);}
   }}
  {QSignalBlocker block(tempo_);tempo_->setValue(project_.bpm);}
  arrangement_->setMinimumHeight(std::max(400,34+int(project_.tracks.size())*lane_px));
  select(selected_);setWindowTitle("NoeMixerr | "+QString::fromStdString(project_.name));
 }
 void open(){auto path=QFileDialog::getOpenFileName(this,"Open project",{},"NoeMixerr (*.noemix)");if(path.isEmpty())return;
  safe([&]{stop();project_=noemix::open_project(path.toStdString());filename_=path;selected_=0;refresh();});}
 void save(){auto path=filename_.isEmpty()?QFileDialog::getSaveFileName(this,"Save project",{},"NoeMixerr (*.noemix)"):filename_;
  if(path.isEmpty())return;if(!path.endsWith(".noemix",Qt::CaseInsensitive))path+=".noemix";
  safe([&]{noemix::save_project(project_,path.toStdString());filename_=path;statusBar()->showMessage("Session saved",3500);});}
 void importAudio(){if(project_.tracks.empty())project_.tracks.push_back(noemix::Track{});
  auto path=QFileDialog::getOpenFileName(this,"Import WAV",{},"PCM WAV (*.wav)");if(path.isEmpty())return;
  safe([&]{auto c=noemix::read_wav(path.toStdString());project_.tracks[size_t(selected_)].clips.push_back(std::move(c));refresh();});}
 void exportAudio(){auto path=QFileDialog::getSaveFileName(this,"Bounce mix",{},"WAV (*.wav)");if(path.isEmpty())return;
  if(!path.endsWith(".wav",Qt::CaseInsensitive))path+=".wav";
  safe([&]{noemix::write_wav(project_,path.toStdString());statusBar()->showMessage("Exported "+path,5000);});}
 void play(){safe([&]{if(!temp_.isValid())throw std::runtime_error("Temporary directory unavailable");
  stop();const auto path=temp_.path()+"/mix.wav";
  noemix::write_wav(project_,path.toStdString());
  player_.setSource(QUrl());player_.setSource(QUrl::fromLocalFile(path));player_.play();
  statusBar()->showMessage("Playing preview mix",4000);
 });}
};
}
int main(int argc,char** argv){QApplication app(argc,argv);app.setApplicationName("NoeMixerr");Workstation w;w.show();return app.exec();}
