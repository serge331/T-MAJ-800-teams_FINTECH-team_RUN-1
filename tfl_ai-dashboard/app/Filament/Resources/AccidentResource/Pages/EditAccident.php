<?php

namespace App\Filament\Resources\AccidentResource\Pages;

use App\Filament\Resources\AccidentResource;
use Filament\Pages\Actions;
use Filament\Resources\Pages\EditRecord;

class EditAccident extends EditRecord
{
    protected static string $resource = AccidentResource::class;

    protected function getActions(): array
    {
        return [
            Actions\DeleteAction::make(),
        ];
    }
}
