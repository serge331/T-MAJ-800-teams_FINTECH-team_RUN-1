<?php

namespace App\Filament\Pages;

use Filament\Notifications\Notification;
use Filament\Pages\Actions\Action;
use Filament\Pages\Page;
use Illuminate\Support\Facades\Cache;

class Model extends Page
{
    protected static ?string $navigationIcon = 'heroicon-o-document-text';

    protected static string $view = 'filament.pages.model';

    public string $accuracy;

    public function mount()
    {
        $this->accuracy = Cache::get('model_accuracy', '0.0');
    }

    protected function getActions(): array
    {
        return [
            Action::make('create')
                ->label('New Model')
                ->icon('heroicon-o-plus-circle')
                ->action(function () {
                    // get path of new_model.py in public storage
                    $new_model_path = storage_path('app/public/machine-learning/new_model.py');
                    // get dataset path in public storage
                    $dataset_path = storage_path('app/public/machine-learning/dataset_accidents.csv');
                    // output path of new_model.py in public storage
                    $output_path = storage_path('app/public/machine-learning/trained_model.joblib');
                    // execute python script
                    exec("python3 $new_model_path $dataset_path $output_path");
                    $this->accuracy = 0.0;
                    Cache::put('model_accuracy', 0.0);
                    Notification::make()
                        ->title('New Model Created')
                        ->success()
                        ->send();
                }),
            Action::make('refresh_accuracy')
                ->label('Refresh Accuracy')
                ->icon('heroicon-o-refresh')
                ->action(function () {
                    // get path of refresh_accuracy.py in public storage
                    $refresh_accuracy_path = storage_path('app/public/machine-learning/get_model_accuracy.py');
                    // get dataset path in public storage
                    $dataset_path = storage_path('app/public/machine-learning/dataset_accidents.csv');
                    // execute python script
                    $accuracy = exec("python3 $refresh_accuracy_path $dataset_path");
                    $this->accuracy = $accuracy * 100;
                    Cache::put('model_accuracy', $accuracy * 100);
                    Notification::make()
                        ->title('Accuracy Refreshed')
                        ->success()
                        ->send();
                }),
        ];
    }
}
