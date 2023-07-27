<?php

namespace App\Filament\Resources\AccidentResource\Pages;

use App\Filament\Resources\AccidentResource;
use Domain\Accidents\Models\Accident;
use Filament\Notifications\Notification;
use Filament\Pages\Actions\Action;
use Filament\Resources\Pages\Page;

class AccidentAnalysis extends Page
{
    protected static string $resource = AccidentResource::class;

    protected static string $view = 'filament.resources.accident-resource.pages.accident-analysis';

    public Accident $record;

    public function mount(Accident $record)
    {
        $this->record = $record;
    }

    protected function getActions(): array
    {
        return [
            Action::make('analyze')
                ->label('New Analysis')
                ->icon('heroicon-o-chart-pie')
                ->action(function () {
                    // get path of ask_model.py in public storage
                    $ask_model_path = storage_path('app/public/machine-learning/ask_model.py');
                    // get trained model path in public storage
                    $trained_model_path = storage_path('app/public/machine-learning/trained_model.joblib');
                    $data = [
                        [
                            ...array_column($this->record->speed_samples, 'speed'),
                            ...array_column($this->record->rainfall_samples, 'rainfall')
                        ]
                    ];
                    // convert string to float or int for python script
                    $data = array_map(function ($item) {
                        return array_map(function ($item) {
                            return is_numeric($item) ? (float)$item : $item;
                        }, $item);
                    }, $data);
                    // execute python script
                    $prediction = exec("python3 $ask_model_path $trained_model_path " . json_encode($data) . " 2>&1");
                    $this->record->liability = $prediction == 1 ? 'Accident' : 'No Accident';
                    $this->record->save();
                    Notification::make()
                        ->title('Analysis Completed')
                        ->success()
                        ->send();
                })
        ];
    }
}
